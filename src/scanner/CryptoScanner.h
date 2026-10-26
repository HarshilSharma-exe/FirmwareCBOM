#ifndef CRYPTOSCANNER_H
#define CRYPTOSCANNER_H

#include <string>
#include <vector>
#include "../models/CryptoComponent.h"
#include "../database/CryptoDatabase.h"

// Scans a firmware/source file line-by-line looking for known
// cryptographic algorithm keywords, and produces CryptoComponent objects.
class CryptoScanner {
private:
    const CryptoDatabase& database;

    // Returns the canonical algorithm name found in a line, or "" if none found.
    std::string detectAlgorithm(const std::string& line) const;

public:
    explicit CryptoScanner(const CryptoDatabase& db);

    // Scans a single file and returns all detected components.
    std::vector<CryptoComponent> scanFile(const std::string& filename) const;

    // Scans every file in a directory (non-recursive) and merges the results.
    std::vector<CryptoComponent> scanDirectory(const std::string& directoryPath) const;
};

#endif // CRYPTOSCANNER_H
