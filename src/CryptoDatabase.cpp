#include "CryptoDatabase.h"
#include <unordered_map>
#include <algorithm>
#include <cctype>

namespace {

// Normalizes algorithm name (uppercase and alphanumeric) to avoid case sensitivity issues
std::string normalizeName(const std::string& name) {
    std::string normalized;
    for (char ch : name) {
        if (std::isalnum(static_cast<unsigned char>(ch)) || ch == '-') {
            normalized += static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
        }
    }
    return normalized;
}

} // anonymous namespace

/**
 * =========================================================================
 * OOP PILLAR 1: ENCAPSULATION
 * =========================================================================
 * The internal database is encapsulated inside this translation unit.
 * External code cannot modify the database directly; it can only query via findAlgorithm().
 */
std::optional<AlgorithmInfo> CryptoDatabase::findAlgorithm(
    const std::string& algorithmName
) const {
    // Internal knowledge base populated with official NIST and RFC standards
    static const std::unordered_map<std::string, AlgorithmInfo> database = {
        {"AES", {
            "AES",
            "Symmetric Encryption",
            "NIST-approved modern symmetric block cipher. Security relies on key size (128, 192, 256 bits), safe operating mode (e.g., GCM, CCM; avoid ECB), and proper initialization vector (IV) / nonce management.",
            "Use AES in authenticated encryption modes (GCM or CCM) with 128 or 256-bit keys. Never reuse nonces and avoid ECB mode.",
            "NIST FIPS 197 / NIST SP 800-38D"
        }},
        {"DES", {
            "DES",
            "Symmetric Encryption",
            "Legacy symmetric block cipher with a 56-bit effective key size. Vulnerable to practical brute-force key search attacks and disallowed by modern standards.",
            "Deprecate immediately and migrate to AES-128 or AES-256.",
            "NIST SP 800-131A Rev. 2"
        }},
        {"RSA", {
            "RSA",
            "Asymmetric Cryptography",
            "Public-key algorithm used for encryption and digital signatures. Security depends heavily on key size, secure padding (OAEP for encryption, PSS for signatures), and implementation safety.",
            "Ensure a minimum key length of 2048 bits (3072 bits recommended for longer-term security) and employ modern padding schemes (OAEP/PSS).",
            "NIST SP 800-57 Part 1 Rev. 5 / FIPS 186-5"
        }},
        {"ECC", {
            "ECC",
            "Asymmetric Cryptography",
            "Elliptic Curve Cryptography providing high security with compact keys compared to RSA. Security relies on mathematically validated standard curves and side-channel resistance.",
            "Use approved curves such as NIST P-256, P-384, or Curve25519. Validate curve parameters and guard against timing attacks.",
            "NIST SP 800-186 / FIPS 186-5"
        }},
        {"DSA", {
            "DSA",
            "Digital Signature",
            "Legacy Digital Signature Algorithm. FIPS 186-5 disallows DSA for digital signature generation due to vulnerability to predictable nonce attacks and performance constraints.",
            "Transition to modern digital signature schemes such as ECDSA, Ed25519, or ML-DSA.",
            "NIST FIPS 186-5 / SP 800-131A Rev. 2"
        }},
        {"SHA-256", {
            "SHA-256",
            "Hash",
            "Secure cryptographic hash function producing a 256-bit digest. Part of the SHA-2 family. Note: Digest length is not an encryption key size.",
            "Approved for general integrity verification, digital signatures, and HMAC construction (HMAC-SHA-256).",
            "NIST FIPS 180-4"
        }},
        {"SHA256", {
            "SHA-256",
            "Hash",
            "Secure cryptographic hash function producing a 256-bit digest. Part of the SHA-2 family. Note: Digest length is not an encryption key size.",
            "Approved for general integrity verification, digital signatures, and HMAC construction (HMAC-SHA-256).",
            "NIST FIPS 180-4"
        }},
        {"SHA-1", {
            "SHA-1",
            "Hash",
            "Legacy 160-bit hash function with proven practical collision vulnerabilities (SHAttered, 2017). Disallowed by NIST for digital signatures and certificates.",
            "Deprecate and migrate to SHA-256, SHA-512, or SHA-3. Acceptable only for legacy HMAC verification where collision resistance is not strictly required.",
            "NIST SP 800-131A Rev. 2 / RFC 6194"
        }},
        {"SHA1", {
            "SHA-1",
            "Hash",
            "Legacy 160-bit hash function with proven practical collision vulnerabilities (SHAttered, 2017). Disallowed by NIST for digital signatures and certificates.",
            "Deprecate and migrate to SHA-256, SHA-512, or SHA-3. Acceptable only for legacy HMAC verification where collision resistance is not strictly required.",
            "NIST SP 800-131A Rev. 2 / RFC 6194"
        }},
        {"MD5", {
            "MD5",
            "Hash",
            "Cryptographically broken 128-bit hash function subject to rapid, trivial collision generation. Cannot guarantee message integrity or authenticity.",
            "Prohibit for any security purpose. Replace with SHA-256 or SHA-3 immediately.",
            "IETF RFC 6151 / NIST SP 800-131A Rev. 2"
        }},
        {"ML-KEM", {
            "ML-KEM",
            "Post-Quantum Cryptography",
            "Module-Lattice-Based Key-Encapsulation Mechanism standardized by NIST for quantum-resistant public-key encryption.",
            "Implement standardized parameter sets (ML-KEM-512, ML-KEM-768, ML-KEM-1024) in hybrid or standalone architectures with constant-time execution.",
            "NIST FIPS 203"
        }},
        {"MLKEM", {
            "ML-KEM",
            "Post-Quantum Cryptography",
            "Module-Lattice-Based Key-Encapsulation Mechanism standardized by NIST for quantum-resistant public-key encryption.",
            "Implement standardized parameter sets (ML-KEM-512, ML-KEM-768, ML-KEM-1024) in hybrid or standalone architectures with constant-time execution.",
            "NIST FIPS 203"
        }},
        {"ML-DSA", {
            "ML-DSA",
            "Post-Quantum Cryptography",
            "Module-Lattice-Based Digital Signature Algorithm standardized by NIST for quantum-resistant digital authentication.",
            "Adopt ML-DSA (ML-DSA-44, ML-DSA-65, ML-DSA-87) for future-proof quantum-resistant digital signing.",
            "NIST FIPS 204"
        }},
        {"MLDSA", {
            "ML-DSA",
            "Post-Quantum Cryptography",
            "Module-Lattice-Based Digital Signature Algorithm standardized by NIST for quantum-resistant digital authentication.",
            "Adopt ML-DSA (ML-DSA-44, ML-DSA-65, ML-DSA-87) for future-proof quantum-resistant digital signing.",
            "NIST FIPS 204"
        }}
    };

    std::string key = normalizeName(algorithmName);
    auto it = database.find(key);
    if (it != database.end()) {
        return it->second;
    }

    return std::nullopt; // Algorithm not recognized
}
