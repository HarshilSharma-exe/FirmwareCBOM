#include "CryptoScanner.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>

namespace fs = std::filesystem;

CryptoScanner::CryptoScanner(const CryptoDatabase& db) : database(db) {}

// Keywords are checked in a specific order so that more-specific matches
// (e.g. "AES-256" style suffixes coming from a call like AES256_encrypt)
// resolve to sensible canonical algorithm names.
std::string CryptoScanner::detectAlgorithm(const std::string& line) const {
    struct KeywordMap { std::string keyword; std::string canonical; };
    static const std::vector<KeywordMap> keywords = {
        {"AES256", "AES-256"}, {"AES_256", "AES-256"}, {"AES-256", "AES-256"},
        {"AES128", "AES-128"}, {"AES_128", "AES-128"}, {"AES-128", "AES-128"},
        {"RSA2048", "RSA-2048"}, {"RSA_2048", "RSA-2048"}, {"RSA-2048", "RSA-2048"},
        {"RSA3072", "RSA-3072"}, {"RSA_3072", "RSA-3072"}, {"RSA-3072", "RSA-3072"},
        {"RSA", "RSA-2048"}, // fallback if no key size is specified
        {"ECDSA", "ECDSA"},
        {"SHA256", "SHA-256"}, {"SHA_256", "SHA-256"}, {"SHA-256", "SHA-256"},
        {"SHA1", "SHA-1"}, {"SHA_1", "SHA-1"}, {"SHA-1", "SHA-1"},
        {"MD5", "MD5"},
        {"DES", "DES"},
    };

    for (const auto& k : keywords) {
        if (line.find(k.keyword) != std::string::npos) {
            return k.canonical;
        }
    }
    return "";
}

std::vector<CryptoComponent> CryptoScanner::scanFile(const std::string& filename) const {
    std::vector<CryptoComponent> found;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Warning: could not open file " << filename << std::endl;
        return found;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::string algorithm = detectAlgorithm(line);
        if (!algorithm.empty()) {
            std::string type = database.isKnown(algorithm)
                                    ? database.getType(algorithm)
                                    : "unknown";
            found.emplace_back(algorithm, type, filename);
        }
    }

    return found;
}

std::vector<CryptoComponent> CryptoScanner::scanDirectory(const std::string& directoryPath) const {
    std::vector<CryptoComponent> allFound;

    if (!fs::exists(directoryPath) || !fs::is_directory(directoryPath)) {
        std::cerr << "Warning: directory not found: " << directoryPath << std::endl;
        return allFound;
    }

    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        if (entry.is_regular_file()) {
            std::vector<CryptoComponent> fileResults = scanFile(entry.path().string());
            allFound.insert(allFound.end(), fileResults.begin(), fileResults.end());
        }
    }

    return allFound;
}
