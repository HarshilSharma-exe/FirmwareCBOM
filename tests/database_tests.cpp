#include <iostream>
#include <cassert>
#include <memory>
#include "BaseDatabase.h"
#include "CryptoDatabase.h"

void testDatabaseLookups() {
    std::cout << "[RUNNING] testDatabaseLookups...\n";
    // Polymorphic pointer to base class
    std::unique_ptr<BaseDatabase> db = std::make_unique<CryptoDatabase>();

    // Test 1: Standard NIST Cipher
    auto aes = db->findAlgorithm("AES");
    assert(aes.has_value());
    assert(aes->algorithmName == "AES");
    assert(aes->category == "Symmetric Encryption");

    // Test 2: Case normalization
    auto sha1 = db->findAlgorithm("sha-1");
    assert(sha1.has_value());
    assert(sha1->algorithmName == "SHA-1");

    // Test 3: Post-quantum algorithm
    auto mlkem = db->findAlgorithm("ML-KEM");
    assert(mlkem.has_value());
    assert(mlkem->category == "Post-Quantum Cryptography");

    // Test 4: Unknown algorithm returns std::nullopt
    auto unknown = db->findAlgorithm("UnknownCipher99");
    assert(!unknown.has_value());

    std::cout << "[PASSED] testDatabaseLookups\n";
}

int main() {
    std::cout << "========================================\n";
    std::cout << "Running CryptoDatabase Tests (Aditya)\n";
    std::cout << "========================================\n";
    testDatabaseLookups();
    std::cout << "All CryptoDatabase tests passed successfully!\n";
    return 0;
}
