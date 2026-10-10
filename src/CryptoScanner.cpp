#include "CryptoScanner.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <set>
#include <stdexcept>

namespace {

// One known cryptographic keyword and what it means.
struct Signature {
    std::string pattern;    // text to look for (UPPERCASE)
    std::string algorithm;  // standard name to report
    std::string type;       // category
    int keySize;            // bits, 0 if not specified
};

// The list of algorithms the scanner knows about.
// IMPORTANT: longer/more specific patterns come first (AES256 before AES),
// so that "AES256" is reported as AES-256 and not also as plain AES.
const std::vector<Signature>& signatures() {
    static const std::vector<Signature> sigs = {
        {"AES256",   "AES-256",  "Symmetric Encryption", 256},
        {"AES-256",  "AES-256",  "Symmetric Encryption", 256},
        {"AES128",   "AES-128",  "Symmetric Encryption", 128},
        {"AES-128",  "AES-128",  "Symmetric Encryption", 128},
        {"AES",      "AES",      "Symmetric Encryption", 0},
        {"3DES",     "3DES",     "Symmetric Encryption", 168},
        {"DES",      "DES",      "Symmetric Encryption", 56},
        {"RSA2048",  "RSA-2048", "Public-Key",           2048},
        {"RSA-2048", "RSA-2048", "Public-Key",           2048},
        {"RSA4096",  "RSA-4096", "Public-Key",           4096},
        {"RSA-4096", "RSA-4096", "Public-Key",           4096},
        {"RSA",      "RSA",      "Public-Key",           0},
        {"ECDSA",    "ECDSA",    "Public-Key (Signature)", 0},
        {"SHA256",   "SHA-256",  "Hash",                 0},
        {"SHA-256",  "SHA-256",  "Hash",                 0},
        {"SHA1",     "SHA-1",    "Hash",                 0},
        {"SHA-1",    "SHA-1",    "Hash",                 0},
        {"MD5",      "MD5",      "Hash",                 0},
    };
    return sigs;
}

std::string toUpper(std::string text) {
    std::transform(text.begin(), text.end(), text.begin(),
                   [](unsigned char c) { return static_cast<char>(std::toupper(c)); });
    return text;
}

// Letters and digits count as "part of a word". Underscore, space, '(' etc. do not.
// This stops "DES" from matching inside words like "DESCRIPTION".
bool isWordChar(char c) {
    return std::isalnum(static_cast<unsigned char>(c)) != 0;
}

// Finds all known algorithms in a single line of text.
std::vector<const Signature*> findInLine(const std::string& rawLine) {
    std::string line = toUpper(rawLine);

    // Ignore anything after "//" so comments are not treated as real usage.
    std::size_t commentStart = line.find("//");
    if (commentStart != std::string::npos) {
        line.erase(commentStart);
    }

    std::vector<bool> used(line.size(), false);  // characters already matched
    std::vector<const Signature*> found;

    for (const Signature& sig : signatures()) {
        std::size_t pos = 0;
        while ((pos = line.find(sig.pattern, pos)) != std::string::npos) {
            std::size_t end = pos + sig.pattern.size();

            bool leftOk = (pos == 0) || !isWordChar(line[pos - 1]);
            bool rightOk = (end == line.size()) || !isWordChar(line[end]);

            bool free = true;
            for (std::size_t i = pos; i < end; ++i) {
                if (used[i]) { free = false; break; }
            }

            if (leftOk && rightOk && free) {
                for (std::size_t i = pos; i < end; ++i) used[i] = true;
                found.push_back(&sig);
                pos = end;
            } else {
                pos += 1;
            }
        }
    }
    return found;
}

}  // namespace

std::vector<CryptoComponent> CryptoScanner::scanFile(const std::string& filename) const {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    std::vector<CryptoComponent> results;
    std::set<std::string> alreadyReported;  // report each algorithm once per file

    std::string line;
    int lineNumber = 0;
    while (std::getline(file, line)) {
        ++lineNumber;
        for (const Signature* sig : findInLine(line)) {
            if (alreadyReported.insert(sig->algorithm).second) {
                results.emplace_back(sig->algorithm, sig->type, sig->keySize,
                                     filename, lineNumber);
            }
        }
    }
    return results;
}
