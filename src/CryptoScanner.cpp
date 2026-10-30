#include "CryptoScanner.h"
#include <sstream>
#include <regex>
#include <algorithm>
#include <cctype>

namespace {

// Helper function to trim whitespace from evidence lines
std::string trim(const std::string& str) {
    auto start = str.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    auto end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);
}

// Scanner rule struct to associate patterns with canonical names
struct ScanRule {
    std::string canonicalName;
    std::string category;
    std::string defaultUsage;
    std::regex pattern;
    bool isHash; // Hashes must NEVER have keySizeBits
};

} // anonymous namespace

/**
 * =========================================================================
 * OOP PILLAR 1: ENCAPSULATION
 * =========================================================================
 * The scanner encapsulates regular expression pattern matching and line parsing.
 */
std::vector<CryptoComponent> CryptoScanner::scan(
    const std::string& sourceCode,
    const std::string& sourceFile
) const {
    std::vector<CryptoComponent> detectedComponents;

    // Ordered list of rules to match against source lines
    // Uses boundaries so we don't accidentally match normal words like 'destination' for DES
    const std::vector<ScanRule> rules = {
        // Post-Quantum
        {"ML-KEM", "Post-Quantum Cryptography", "Key Encapsulation",
         std::regex(R"((?:^|[^a-zA-Z0-9])(ML[-_]?KEM|Kyber)(?:_|\b|[^a-zA-Z0-9]|$))", std::regex_constants::icase), false},
        {"ML-DSA", "Post-Quantum Cryptography", "Digital Signature",
         std::regex(R"((?:^|[^a-zA-Z0-9])(ML[-_]?DSA|Dilithium)(?:_|\b|[^a-zA-Z0-9]|$))", std::regex_constants::icase), false},

        // Hashes
        {"SHA-256", "Hash", "Hashing",
         std::regex(R"((?:^|[^a-zA-Z0-9])(SHA[-_]?256)(?:_|\b|[^a-zA-Z0-9]|$))", std::regex_constants::icase), true},
        {"SHA-1", "Hash", "Hashing",
         std::regex(R"((?:^|[^a-zA-Z0-9])(SHA[-_]?1)(?:_|\b|[^a-zA-Z0-9]|$))", std::regex_constants::icase), true},
        {"MD5", "Hash", "Hashing",
         std::regex(R"((?:^|[^a-zA-Z0-9])(MD5)(?:_|\b|[^a-zA-Z0-9]|$))", std::regex_constants::icase), true},

        // Symmetric Ciphers
        {"DES", "Symmetric Encryption", "Encryption",
         std::regex(R"((?:^|[^a-zA-Z0-9])(3DES|TripleDES|DES)(?:_|\b|[^a-zA-Z0-9]|$))", std::regex_constants::icase), false},
        {"AES", "Symmetric Encryption", "Encryption",
         std::regex(R"((?:^|[^a-zA-Z0-9])(AES|Rijndael)(?:_|\b|[^a-zA-Z0-9]|$))", std::regex_constants::icase), false},

        // Asymmetric / Signatures
        {"RSA", "Asymmetric Cryptography", "Encryption / Signature",
         std::regex(R"((?:^|[^a-zA-Z0-9])(RSA)(?:_|\b|[^a-zA-Z0-9]|$))", std::regex_constants::icase), false},
        {"ECC", "Asymmetric Cryptography", "Key Exchange / Signature",
         std::regex(R"((?:^|[^a-zA-Z0-9])(ECC|ECDSA|ECDH|secp256r1|Curve25519)(?:_|\b|[^a-zA-Z0-9]|$))", std::regex_constants::icase), false},
        {"DSA", "Digital Signature", "Digital Signature",
         std::regex(R"((?:^|[^a-zA-Z0-9])(DSA)(?:_|\b|[^a-zA-Z0-9]|$))", std::regex_constants::icase), false}
    };

    std::istringstream stream(sourceCode);
    std::string line;
    int currentLineNumber = 0;

    while (std::getline(stream, line)) {
        currentLineNumber++;
        std::string trimmedLine = trim(line);
        if (trimmedLine.empty()) {
            continue;
        }

        for (const auto& rule : rules) {
            std::smatch match;
            if (std::regex_search(line, match, rule.pattern)) {
                CryptoComponent comp;
                comp.algorithmName = rule.canonicalName;
                comp.category = rule.category;
                comp.usage = rule.defaultUsage;
                comp.sourceFile = sourceFile;
                comp.lineNumber = currentLineNumber;
                comp.evidence = trimmedLine;

                // For hashes, keySizeBits is strictly std::nullopt (hashes have digests, not keys)
                if (rule.isHash) {
                    comp.keySizeBits = std::nullopt;
                } else {
                    // Search for key sizes (128, 192, 256, 512, 1024, 2048, 4096)
                    std::regex keyRegex(R"(\b(128|192|256|512|1024|2048|3072|4096)\b)");
                    std::smatch keyMatch;
                    if (std::regex_search(line, keyMatch, keyRegex)) {
                        comp.keySizeBits = std::stoi(keyMatch.str(1));
                    } else {
                        comp.keySizeBits = std::nullopt;
                    }
                }

                detectedComponents.push_back(comp);
            }
        }
    }

    return detectedComponents;
}
