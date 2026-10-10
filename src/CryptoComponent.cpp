#include "CryptoComponent.h"

#include <iostream>

CryptoComponent::CryptoComponent(const std::string& alg,
                                 const std::string& t,
                                 int key,
                                 const std::string& file,
                                 int line)
    : algorithm(alg),
      type(t),
      keySize(key),
      sourceFile(file),
      lineNumber(line) {}

std::string CryptoComponent::getAlgorithm() const { return algorithm; }
std::string CryptoComponent::getType() const { return type; }
int CryptoComponent::getKeySize() const { return keySize; }
std::string CryptoComponent::getSourceFile() const { return sourceFile; }
int CryptoComponent::getLineNumber() const { return lineNumber; }

void CryptoComponent::display() const {
    std::cout << "Algorithm : " << algorithm << "\n";
    std::cout << "Type      : " << type << "\n";
    if (keySize > 0) {
        std::cout << "Key size  : " << keySize << " bits\n";
    } else {
        std::cout << "Key size  : not specified\n";
    }
    std::cout << "Found in  : " << sourceFile << " (line " << lineNumber << ")\n";
}
