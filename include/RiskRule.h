#ifndef RISK_RULE_H
#define RISK_RULE_H

#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include "CryptoComponent.h"
#include "AlgorithmInfo.h"
#include "RiskFinding.h"

/**
 * =========================================================================
 * OOP PILLAR 2 & 4: ABSTRACTION & POLYMORPHISM (Abstract Base Class)
 * =========================================================================
 * RiskRule is an Abstract Base Class.
 * It defines pure virtual functions (= 0), which means:
 *  1. You cannot instantiate RiskRule directly.
 *  2. Any derived class MUST implement these methods.
 *  3. Callers can use a base class pointer (RiskRule*) to call methods polymorphically.
 */
class RiskRule {
public:
    // Virtual destructor is crucial in base classes to prevent memory leaks when deleting via base pointer
    virtual ~RiskRule() = default;

    // Pure virtual method: Returns true if this rule applies to the given component
    virtual bool applies(const CryptoComponent& component, const AlgorithmInfo& info) const = 0;

    // Pure virtual method: Evaluates risk and returns an explainable finding
    virtual RiskFinding evaluate(const CryptoComponent& component, const AlgorithmInfo& info) const = 0;
};

/**
 * =========================================================================
 * OOP PILLAR 3: INHERITANCE (Derived Class 1: Legacy Ciphers)
 * =========================================================================
 * LegacyCipherRule 'is-a' RiskRule.
 * It inherits from RiskRule and overrides the pure virtual functions.
 */
class LegacyCipherRule : public RiskRule {
public:
    bool applies(const CryptoComponent&, const AlgorithmInfo& info) const override {
        return info.algorithmName == "DES";
    }

    RiskFinding evaluate(const CryptoComponent& component, const AlgorithmInfo&) const override {
        RiskFinding finding;
        finding.algorithmName = component.algorithmName;
        finding.severity = "High";
        finding.reason = "DES utilizes an insecure 56-bit effective key length vulnerable to practical brute-force recovery (NIST SP 800-131A).";
        finding.recommendation = "Deprecate immediately and migrate to AES-128 or AES-256.";
        finding.sourceFile = component.sourceFile;
        finding.lineNumber = component.lineNumber;
        return finding;
    }
};

/**
 * =========================================================================
 * OOP PILLAR 3: INHERITANCE (Derived Class 2: Broken Hashes)
 * =========================================================================
 * BrokenHashRule 'is-a' RiskRule.
 * Specializes in evaluating collision-vulnerable hash functions (MD5 and SHA-1).
 */
class BrokenHashRule : public RiskRule {
public:
    bool applies(const CryptoComponent&, const AlgorithmInfo& info) const override {
        return info.algorithmName == "MD5" || info.algorithmName == "SHA-1";
    }

    RiskFinding evaluate(const CryptoComponent& component, const AlgorithmInfo& info) const override {
        RiskFinding finding;
        finding.algorithmName = component.algorithmName;
        finding.sourceFile = component.sourceFile;
        finding.lineNumber = component.lineNumber;

        if (info.algorithmName == "MD5") {
            finding.severity = "High";
            finding.reason = "MD5 has severe collision vulnerabilities allowing rapid practical forgery (RFC 6151).";
            finding.recommendation = "Do not use for security purposes. Migrate immediately to SHA-256 or SHA-3.";
        } else {
            finding.severity = "Medium";
            finding.reason = "SHA-1 possesses demonstrated collision attacks (SHAttered) and is disallowed by NIST for certificates and signatures.";
            finding.recommendation = "Migrate to SHA-256, SHA-512, or SHA-3. Acceptable only for legacy HMAC verification where collision resistance is not strictly required.";
        }
        return finding;
    }
};

/**
 * =========================================================================
 * OOP PILLAR 3: INHERITANCE (Derived Class 3: Key Length Verification)
 * =========================================================================
 * KeyLengthRule 'is-a' RiskRule.
 * Checks key size parameters (e.g. RSA keys under 2048 bits are insecure).
 */
class KeyLengthRule : public RiskRule {
public:
    bool applies(const CryptoComponent&, const AlgorithmInfo& info) const override {
        return info.algorithmName == "RSA";
    }

    RiskFinding evaluate(const CryptoComponent& component, const AlgorithmInfo&) const override {
        RiskFinding finding;
        finding.algorithmName = component.algorithmName;
        finding.sourceFile = component.sourceFile;
        finding.lineNumber = component.lineNumber;

        if (component.keySizeBits.has_value()) {
            int bits = *component.keySizeBits;
            if (bits < 2048) {
                finding.severity = "High";
                finding.reason = "RSA key size (" + std::to_string(bits) +
                                 " bits) is below the minimum NIST guideline of 2048 bits and vulnerable to factorization attacks.";
                finding.recommendation = "Upgrade RSA key length to at least 2048 bits (3072+ bits recommended).";
            } else {
                finding.severity = "Informational";
                finding.reason = "RSA key size (" + std::to_string(bits) + " bits) meets NIST minimum length requirements.";
                finding.recommendation = "Ensure modern padding schemes (OAEP for encryption, PSS for signatures) and protect against side channels.";
            }
        } else {
            finding.severity = "Manual Review";
            finding.reason = "The source reference does not establish the RSA key length or padding scheme.";
            finding.recommendation = "Verify key length (>= 2048 bits) and verify use of secure padding (OAEP/PSS).";
        }
        return finding;
    }
};

/**
 * =========================================================================
 * OOP PILLAR 3: INHERITANCE (Derived Class 4: Symmetric Cipher Mode)
 * =========================================================================
 * SymmetricModeRule 'is-a' RiskRule.
 * Checks cipher modes (e.g. ECB is insecure, GCM is secure).
 */
class SymmetricModeRule : public RiskRule {
private:
    static bool containsIgnoreCase(const std::string& str, const std::string& substr) {
        auto it = std::search(
            str.begin(), str.end(),
            substr.begin(), substr.end(),
            [](char ch1, char ch2) {
                return std::tolower(static_cast<unsigned char>(ch1)) ==
                       std::tolower(static_cast<unsigned char>(ch2));
            }
        );
        return it != str.end();
    }

public:
    bool applies(const CryptoComponent&, const AlgorithmInfo& info) const override {
        return info.algorithmName == "AES";
    }

    RiskFinding evaluate(const CryptoComponent& component, const AlgorithmInfo&) const override {
        RiskFinding finding;
        finding.algorithmName = component.algorithmName;
        finding.sourceFile = component.sourceFile;
        finding.lineNumber = component.lineNumber;

        if (containsIgnoreCase(component.evidence, "ECB")) {
            finding.severity = "High";
            finding.reason = "AES appears to be configured in ECB (Electronic Codebook) mode, which leaks plaintext patterns.";
            finding.recommendation = "Switch to an authenticated mode such as AES-GCM or AES-CCM.";
            return finding;
        }

        if (component.keySizeBits.has_value() && *component.keySizeBits < 128) {
            finding.severity = "High";
            finding.reason = "AES key size (" + std::to_string(*component.keySizeBits) + " bits) is below the 128-bit standard.";
            finding.recommendation = "Use 128, 192, or 256-bit keys.";
            return finding;
        }

        if (containsIgnoreCase(component.evidence, "GCM") || containsIgnoreCase(component.evidence, "CCM")) {
            finding.severity = "Informational";
            finding.reason = "AES is used in an authenticated encryption mode (GCM/CCM).";
            finding.recommendation = "Ensure unique IV/nonce for each encryption operation and secure key storage.";
            return finding;
        }

        finding.severity = "Manual Review";
        finding.reason = "The source reference does not establish mode or key management.";
        finding.recommendation = "Review configuration and key handling.";
        return finding;
    }
};

/**
 * =========================================================================
 * OOP PILLAR 3: INHERITANCE (Derived Class 5: Modern & Post-Quantum Rules)
 * =========================================================================
 * StandardAndPostQuantumRule 'is-a' RiskRule.
 * Handles SHA-256, ML-KEM, ML-DSA, ECC, DSA.
 */
class StandardAndPostQuantumRule : public RiskRule {
public:
    bool applies(const CryptoComponent&, const AlgorithmInfo& info) const override {
        return info.algorithmName == "SHA-256" ||
               info.algorithmName == "ML-KEM" ||
               info.algorithmName == "ML-DSA" ||
               info.algorithmName == "DSA" ||
               info.algorithmName == "ECC";
    }

    RiskFinding evaluate(const CryptoComponent& component, const AlgorithmInfo& info) const override {
        RiskFinding finding;
        finding.algorithmName = component.algorithmName;
        finding.sourceFile = component.sourceFile;
        finding.lineNumber = component.lineNumber;

        if (info.algorithmName == "SHA-256") {
            finding.severity = "Informational";
            finding.reason = "SHA-256 is an approved, secure cryptographic hash function with no known collision attacks.";
            finding.recommendation = "Approved for integrity and signatures. Use HMAC-SHA-256 to prevent length-extension attacks when authenticating.";
        } else if (info.algorithmName == "DSA") {
            finding.severity = "Medium";
            finding.reason = "DSA is disallowed for modern digital signature generation in NIST FIPS 186-5 due to parameter limitations and vulnerability to nonce exposure.";
            finding.recommendation = "Transition to modern schemes such as ECDSA (e.g., P-256), Ed25519, or quantum-resistant ML-DSA.";
        } else if (info.algorithmName == "ECC") {
            finding.severity = "Manual Review";
            finding.reason = "Source reference does not confirm curve parameters or validation checks.";
            finding.recommendation = "Confirm use of approved curves (e.g., NIST P-256, Curve25519) and verify side-channel mitigations.";
        } else {
            finding.severity = "Informational";
            finding.reason = info.algorithmName + " is a standardized post-quantum cryptographic algorithm compliant with NIST FIPS 203/204.";
            finding.recommendation = "Verify standardized parameter sets and ensure constant-time implementations against side channels.";
        }
        return finding;
    }
};

#endif
