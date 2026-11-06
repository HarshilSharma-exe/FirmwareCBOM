#include "CBOMGenerator.h"
#include <sstream>
#include <iomanip>

namespace {

// Helper to escape characters in strings according to JSON RFC 8259
std::string escapeJson(const std::string& input) {
    std::ostringstream ss;
    for (char c : input) {
        switch (c) {
            case '"':  ss << "\\\""; break;
            case '\\': ss << "\\\\"; break;
            case '\b': ss << "\\b"; break;
            case '\f': ss << "\\f"; break;
            case '\n': ss << "\\n"; break;
            case '\r': ss << "\\r"; break;
            case '\t': ss << "\\t"; break;
            default:
                if (static_cast<unsigned char>(c) < 0x20) {
                    ss << "\\u" << std::hex << std::setw(4) << std::setfill('0') << static_cast<int>(c);
                } else {
                    ss << c;
                }
                break;
        }
    }
    return ss.str();
}

} // anonymous namespace

/**
 * Polymorphic implementation of BaseReportGenerator::generate
 */
std::string CBOMGenerator::generate(
    const std::vector<CryptoComponent>& components,
    const std::vector<RiskFinding>& findings
) const {
    return generateJson(components, findings);
}

std::string CBOMGenerator::generateJson(
    const std::vector<CryptoComponent>& components,
    const std::vector<RiskFinding>& findings
) const {
    std::ostringstream json;

    json << "{\n";
    json << "  \"schemaVersion\": \"1.0\",\n";

    // Serialize components array
    json << "  \"components\": [";
    for (size_t i = 0; i < components.size(); ++i) {
        const auto& c = components[i];
        json << "\n    {\n";
        json << "      \"algorithmName\": \"" << escapeJson(c.algorithmName) << "\",\n";
        json << "      \"category\": \"" << escapeJson(c.category) << "\",\n";
        json << "      \"usage\": \"" << escapeJson(c.usage) << "\",\n";

        json << "      \"keySizeBits\": ";
        if (c.keySizeBits.has_value()) {
            json << *c.keySizeBits;
        } else {
            json << "null";
        }
        json << ",\n";

        json << "      \"sourceFile\": \"" << escapeJson(c.sourceFile) << "\",\n";
        json << "      \"lineNumber\": " << c.lineNumber << ",\n";
        json << "      \"evidence\": \"" << escapeJson(c.evidence) << "\"\n";
        json << "    }";
        if (i + 1 < components.size()) {
            json << ",";
        }
    }
    if (!components.empty()) {
        json << "\n  ";
    }
    json << "],\n";

    // Serialize findings array
    json << "  \"findings\": [";
    for (size_t i = 0; i < findings.size(); ++i) {
        const auto& f = findings[i];
        json << "\n    {\n";
        json << "      \"algorithmName\": \"" << escapeJson(f.algorithmName) << "\",\n";
        json << "      \"severity\": \"" << escapeJson(f.severity) << "\",\n";
        json << "      \"reason\": \"" << escapeJson(f.reason) << "\",\n";
        json << "      \"recommendation\": \"" << escapeJson(f.recommendation) << "\",\n";
        json << "      \"sourceFile\": \"" << escapeJson(f.sourceFile) << "\",\n";
        json << "      \"lineNumber\": " << f.lineNumber << "\n";
        json << "    }";
        if (i + 1 < findings.size()) {
            json << ",";
        }
    }
    if (!findings.empty()) {
        json << "\n  ";
    }
    json << "]\n";
    json << "}\n";

    return json.str();
}
