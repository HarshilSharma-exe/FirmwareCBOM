#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include "CBOMGenerator.h"

void testReportJsonGeneration() {
    std::cout << "[RUNNING] testReportJsonGeneration...\n";
    CBOMGenerator generator;

    std::vector<CryptoComponent> components;
    CryptoComponent c1;
    c1.algorithmName = "AES";
    c1.category = "Symmetric Encryption";
    c1.usage = "Encryption";
    c1.keySizeBits = 256;
    c1.sourceFile = "sample.cpp";
    c1.lineNumber = 18;
    c1.evidence = "AES_encrypt(\"my_secret\", buf);";
    components.push_back(c1);

    CryptoComponent c2;
    c2.algorithmName = "SHA-256";
    c2.category = "Hash";
    c2.usage = "Hashing";
    c2.keySizeBits = std::nullopt; // Hash has no key size -> should be bare null in JSON
    c2.sourceFile = "sample.cpp";
    c2.lineNumber = 25;
    c2.evidence = "SHA256_Init(&ctx);";
    components.push_back(c2);

    std::vector<RiskFinding> findings;
    RiskFinding f1;
    f1.algorithmName = "AES";
    f1.severity = "Manual Review";
    f1.reason = "The source reference does not establish mode or key management.";
    f1.recommendation = "Review configuration and key handling.";
    f1.sourceFile = "sample.cpp";
    f1.lineNumber = 18;
    findings.push_back(f1);

    std::string json = generator.generateJson(components, findings);

    assert(json.find("\"schemaVersion\": \"1.0\"") != std::string::npos);
    assert(json.find("\"algorithmName\": \"AES\"") != std::string::npos);
    assert(json.find("\"keySizeBits\": 256") != std::string::npos);
    assert(json.find("\"keySizeBits\": null") != std::string::npos);
    assert(json.find("\"keySizeBits\": \"null\"") == std::string::npos); // Must be bare null!
    assert(json.find("\\\"my_secret\\\"") != std::string::npos); // Escaped quote check

    std::cout << "[PASSED] testReportJsonGeneration\n";
}

int main() {
    std::cout << "========================================\n";
    std::cout << "Running CBOMGenerator Tests\n";
    std::cout << "========================================\n";
    testReportJsonGeneration();
    std::cout << "All CBOMGenerator tests passed successfully!\n";
    return 0;
}
