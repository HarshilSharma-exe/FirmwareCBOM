#ifndef CRYPTO_SCANNER_H
#define CRYPTO_SCANNER_H

#include <string>
#include <vector>

#include "CryptoComponent.h"

// CryptoScanner reads a firmware source file line by line and
// reports every cryptographic algorithm it recognises.
// It only answers "WHAT did I find?" - it does not judge whether it is safe.
class CryptoScanner {
public:
    // Scans one file. Throws std::runtime_error if the file cannot be opened.
    std::vector<CryptoComponent> scanFile(const std::string& filename) const;
};

#endif
