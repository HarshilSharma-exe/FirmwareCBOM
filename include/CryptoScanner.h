#ifndef CRYPTO_SCANNER_H
#define CRYPTO_SCANNER_H

#include <string>
#include <vector>
#include "BaseScanner.h"
#include "CryptoComponent.h"

/**
 * =========================================================================
 * OOP: INHERITANCE (HARSHIL'S MODULE)
 * =========================================================================
 * CryptoScanner inherits from BaseScanner.
 * It encapsulates regex pattern recognition and line tracking.
 */
class CryptoScanner : public BaseScanner {
public:
    std::vector<CryptoComponent> scan(
        const std::string& sourceCode,
        const std::string& sourceFile
    ) const override;
};

#endif
