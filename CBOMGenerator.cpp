#include "CBOMGenerator.h"

#include <fstream>
#include <iomanip>
#include <map>
#include <sstream>
#include <stdexcept>

std::string CBOMGenerator::escapeJson(const std::string& text) {
    std::ostringstream out;
    for (unsigned char c : text) {
        switch (c) {
            case '"':  out << "\\\""; break;
            case '\\': out << "\\\\"; break;
            case '\n': out << "\\n";  break;
            case '\r': out << "\\r";  break;
            case '\t': out << "\\t";  break;
            default:
                if (c < 0x20) {
                    // other control characters must be written as \u00XX in JSON
                    out << "\\u" << std::hex << std::setw(4) << std::setfill('0')
                        << static_cast<int>(c) << std::dec << std::setfill(' ');
                } else {
                    out << static_cast<char>(c);
                }
        }
    }
    return out.str();
}

std::string CBOMGenerator::toJSON(const std::vector<CryptoComponent>& components,
                                  const std::string& firmwareName) const {
    std::ostringstream out;
    out << "{\n";
    out << "  \"bomFormat\": \"FirmwareCBOM\",\n";
    out << "  \"formatVersion\": \"0.1\",\n";
    out << "  \"firmware\": \"" << escapeJson(firmwareName) << "\",\n";
    out << "  \"totalComponents\": " << components.size() << ",\n";

    if (components.empty()) {
        out << "  \"components\": []\n";
    } else {
        out << "  \"components\": [\n";
        for (std::size_t i = 0; i < components.size(); ++i) {
            const CryptoComponent& c = components[i];
            out << "    {\n";
            out << "      \"algorithm\": \"" << escapeJson(c.getAlgorithm()) << "\",\n";
            out << "      \"type\": \"" << escapeJson(c.getType()) << "\",\n";
            if (c.getKeySize() > 0) {
                out << "      \"keySize\": " << c.getKeySize() << ",\n";
            } else {
                out << "      \"keySize\": null,\n";   // unknown / not applicable
            }
            out << "      \"file\": \"" << escapeJson(c.getSourceFile()) << "\",\n";
            out << "      \"line\": " << c.getLineNumber() << "\n";
            out << "    }" << (i + 1 < components.size() ? "," : "") << "\n";
        }
        out << "  ]\n";
    }

    out << "}\n";
    return out.str();
}

std::string CBOMGenerator::toTextReport(const std::vector<CryptoComponent>& components,
                                        const std::string& firmwareName) const {
    std::ostringstream out;
    out << "==================================================\n";
    out << " FirmwareCBOM Report\n";
    out << "==================================================\n";
    out << "Firmware         : " << firmwareName << "\n";
    out << "Total components: " << components.size() << "\n\n";

    out << std::left << std::setw(12) << "Algorithm"
        << std::setw(26) << "Type"
        << std::setw(10) << "Key size"
        << "Location\n";
    out << std::string(80, '-') << "\n";

    std::map<std::string, int> countByType;
    for (const CryptoComponent& c : components) {
        std::string key = (c.getKeySize() > 0) ? std::to_string(c.getKeySize()) + " bit"
                                               : "n/a";
        out << std::left << std::setw(12) << c.getAlgorithm()
            << std::setw(26) << c.getType()
            << std::setw(10) << key
            << c.getSourceFile() << ":" << c.getLineNumber() << "\n";
        ++countByType[c.getType()];
    }

    out << "\nSummary by type:\n";
    for (const auto& entry : countByType) {
        out << "  " << std::left << std::setw(26) << entry.first << entry.second << "\n";
    }

    out << "\nNote: risk assessment is not included yet (planned next phase).\n";
    return out.str();
}

void CBOMGenerator::writeToFile(const std::string& path, const std::string& content) const {
    std::ofstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot write file: " + path);
    }
    file << content;
}
