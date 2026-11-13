#include <iostream>
#include <cassert>
#include <string>
#include "RiskAnalyzer.h"

void testRiskAnalyzerRules() {
    std::cout << "[RUNNING] testRiskAnalyzerRules...\n";
    RiskAnalyzer analyzer;

    // Test 1: Unknown cipher flags "Manual Review"
    CryptoComponent unknownComp;
    unknownComp.algorithmName = "SuperSecretCipher";
    unknownComp.sourceFile = "driver.cpp";
    unknownComp.lineNumber = 42;
    unknownComp.evidence = "SuperSecretCipher_init()";

    auto unknownFinding = analyzer.assessRisk(unknownComp, std::nullopt);
    assert(unknownFinding.severity == "Manual Review");
    assert(unknownFinding.lineNumber == 42);

    // Test 2: DES evaluates to High via LegacyCipherRule
    CryptoComponent desComp;
    desComp.algorithmName = "DES";
    desComp.sourceFile = "legacy.cpp";
    desComp.lineNumber = 15;
    desComp.evidence = "des_encrypt(...)";

    AlgorithmInfo desInfo{"DES", "Symmetric Encryption", "Legacy", "Migrate", "NIST"};
    auto desFinding = analyzer.assessRisk(desComp, desInfo);
    assert(desFinding.severity == "High");

    // Test 3: MD5 evaluates to High via BrokenHashRule
    CryptoComponent md5Comp;
    md5Comp.algorithmName = "MD5";
    md5Comp.sourceFile = "auth.cpp";
    md5Comp.lineNumber = 88;
    md5Comp.evidence = "MD5_Init(&ctx)";

    AlgorithmInfo md5Info{"MD5", "Hash", "Broken", "Migrate", "RFC 6151"};
    auto md5Finding = analyzer.assessRisk(md5Comp, md5Info);
    assert(md5Finding.severity == "High");

    // Test 4: Weak RSA key (<2048) evaluates to High via KeyLengthRule
    CryptoComponent rsaWeakComp;
    rsaWeakComp.algorithmName = "RSA";
    rsaWeakComp.keySizeBits = 1024;
    rsaWeakComp.sourceFile = "tls.cpp";
    rsaWeakComp.lineNumber = 100;
    rsaWeakComp.evidence = "RSA_generate_key(1024, ...)";

    AlgorithmInfo rsaInfo{"RSA", "Asymmetric Cryptography", "Public Key", "2048+ bits", "NIST"};
    auto rsaWeakFinding = analyzer.assessRisk(rsaWeakComp, rsaInfo);
    assert(rsaWeakFinding.severity == "High");

    // Test 5: Standard SHA-256 evaluates to Informational
    CryptoComponent shaComp;
    shaComp.algorithmName = "SHA-256";
    shaComp.sourceFile = "bootloader.cpp";
    shaComp.lineNumber = 12;
    shaComp.evidence = "SHA256_Init(&ctx)";

    AlgorithmInfo shaInfo{"SHA-256", "Hash", "Secure", "Approved", "NIST"};
    auto shaFinding = analyzer.assessRisk(shaComp, shaInfo);
    assert(shaFinding.severity == "Informational");

    std::cout << "[PASSED] testRiskAnalyzerRules\n";
}

int main() {
    std::cout << "========================================\n";
    std::cout << "Running RiskAnalyzer Tests (Aditya)\n";
    std::cout << "========================================\n";
    testRiskAnalyzerRules();
    std::cout << "All RiskAnalyzer tests passed successfully!\n";
    return 0;
}
