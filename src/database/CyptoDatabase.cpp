#include "CryptoDatabase.h"

CryptoDatabase::CryptoDatabase() {
    seedDatabase();
}

void CryptoDatabase::seedDatabase() {
    database["AES-128"]  = { "encryption", 2, false, "Acceptable for most use cases" };
    database["AES-256"]  = { "encryption", 1, false, "Safe, recommended" };
    database["RSA-2048"] = { "public-key", 2, false, "Classical-safe, not quantum-safe; plan PQC migration" };
    database["RSA-3072"] = { "public-key", 2, false, "Classical-safe, not quantum-safe; plan PQC migration" };
    database["ECDSA"]    = { "public-key", 2, false, "Classical-safe, not quantum-safe; migrate to ML-DSA" };
    database["SHA-256"]  = { "hash",       1, false, "Safe, recommended" };
    database["SHA-1"]    = { "hash",       4, true,  "Weak, replace with SHA-256" };
    database["MD5"]      = { "hash",       5, true,  "Critical, must be replaced immediately" };
    database["DES"]      = { "encryption", 5, true,  "Critical, must be replaced with AES" };
}

bool CryptoDatabase::isKnown(const std::string& algorithm) const {
    return database.find(algorithm) != database.end();
}

std::string CryptoDatabase::getType(const std::string& algorithm) const {
    auto it = database.find(algorithm);
    return it != database.end() ? it->second.type : "unknown";
}

int CryptoDatabase::getRiskScore(const std::string& algorithm) const {
    auto it = database.find(algorithm);
    return it != database.end() ? it->second.riskScore : 3; // default: MEDIUM-ish for unknown
}

bool CryptoDatabase::isDeprecated(const std::string& algorithm) const {
    auto it = database.find(algorithm);
    return it != database.end() ? it->second.deprecated : false;
}

std::string CryptoDatabase::getRecommendation(const std::string& algorithm) const {
    auto it = database.find(algorithm);
    return it != database.end() ? it->second.recommendation : "No data available; review manually";
}
