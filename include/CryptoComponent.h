#ifndef CRYPTO_COMPONENT_H
#define CRYPTO_COMPONENT_H

#include <string>

// CryptoComponent represents ONE cryptographic item found in firmware.
// Example: "AES-256, Symmetric Encryption, found in sensor.cpp at line 12".
class CryptoComponent {
private:
    std::string algorithm;   // e.g. "AES-256", "SHA-1"
    std::string type;        // e.g. "Symmetric Encryption", "Hash"
    int keySize;             // in bits; 0 means "not specified" (hashes, or unknown)
    std::string sourceFile;  // which firmware file it was found in
    int lineNumber;          // which line of that file

public:
    // Constructor: sets all the data when the object is created
    CryptoComponent(const std::string& alg,
                    const std::string& t,
                    int key,
                    const std::string& file,
                    int line);

    // Getters: private data can only be read through these functions (encapsulation)
    std::string getAlgorithm() const;
    std::string getType() const;
    int getKeySize() const;
    std::string getSourceFile() const;
    int getLineNumber() const;

    // Prints the component in a readable form
    void display() const;
};

#endif
