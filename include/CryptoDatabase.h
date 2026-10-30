#ifndef CRYPTO_DATABASE_H
#define CRYPTO_DATABASE_H

#include <optional>
#include <string>
#include "BaseDatabase.h"
#include "AlgorithmInfo.h"

/**
 * =========================================================================
 * OOP: INHERITANCE & ENCAPSULATION (ADITYA'S MODULE)
 * =========================================================================
 * CryptoDatabase inherits from BaseDatabase.
 * Encapsulates official NIST/RFC standards and normalization algorithms.
 */
class CryptoDatabase : public BaseDatabase {
public:
    std::optional<AlgorithmInfo> findAlgorithm(
        const std::string& algorithmName
    ) const override;
};

#endif
