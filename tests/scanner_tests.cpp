#include <iostream>
#include <cassert>
#include <string>
#include "CryptoScanner.h"

void testScannerWithCryptoPatterns() {
    std::cout << "[RUNNING] testScannerWithCryptoPatterns...\n";
    CryptoScanner scanner;

    std::string sample =
        "// Embedded crypto routine\n"
        "uint8_t buffer[128];\n"
        "AES_encrypt(buffer, 256);\n"
        "SHA-256_hash(data);\n";

    auto components = scanner.scan(sample, "test_file.cpp");

    assert(components.size() == 2);

    // Component 1: AES
    assert(components[0].algorithmName == "AES");
    assert(components[0].lineNumber == 3);
    assert(components[0].keySizeBits.has_value());
    assert(*components[0].keySizeBits == 256);

    // Component 2: SHA-256
    assert(components[1].algorithmName == "SHA-256");
    assert(components[1].lineNumber == 4);
    assert(!components[1].keySizeBits.has_value()); // Hashes have no key size

    std::cout << "[PASSED] testScannerWithCryptoPatterns\n";
}

void testScannerNoCrypto() {
    std::cout << "[RUNNING] testScannerNoCrypto...\n";
    CryptoScanner scanner;

    std::string cleanCode =
        "int add(int a, int b) {\n"
        "    return a + b;\n"
        "}\n";

    auto components = scanner.scan(cleanCode, "math.cpp");
    assert(components.empty());

    std::cout << "[PASSED] testScannerNoCrypto\n";
}

int main() {
    std::cout << "========================================\n";
    std::cout << "Running CryptoScanner Tests\n";
    std::cout << "========================================\n";
    testScannerWithCryptoPatterns();
    testScannerNoCrypto();
    std::cout << "All CryptoScanner tests passed successfully!\n";
    return 0;
}
