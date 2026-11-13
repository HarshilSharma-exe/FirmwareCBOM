#ifndef ALGORITHM_INFO_H
#define ALGORITHM_INFO_H

#include <string>

// Structure to hold authoritative security reference information about an algorithm
struct AlgorithmInfo {
    std::string algorithmName;     // e.g. "AES", "DES", "SHA-256"
    std::string category;          // e.g. "Symmetric Encryption", "Hash"
    std::string securityGuidance;  // Brief explanation of security status
    std::string recommendedAction; // Suggested migration or implementation guidance
    std::string reference;         // Authoritative standard (e.g. NIST FIPS 197)
};

#endif
