#ifndef BASE_SCANNER_H
#define BASE_SCANNER_H

#include <string>
#include <vector>
#include "CryptoComponent.h"

/**
 * =========================================================================
 * OOP: ABSTRACTION & BASE CLASS (HARSHIL'S MODULE)
 * =========================================================================
 * BaseScanner defines the abstract interface for all scanners.
 * Enables future scanners (e.g. BinaryScanner, ASTScanner) to be used polymorphically.
 */
class BaseScanner {
public:
    virtual ~BaseScanner() = default;

    // Pure virtual method
    virtual std::vector<CryptoComponent> scan(
        const std::string& sourceCode,
        const std::string& sourceFile
    ) const = 0;
};

#endif
