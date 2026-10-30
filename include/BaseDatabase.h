#ifndef BASE_DATABASE_H
#define BASE_DATABASE_H

#include <optional>
#include <string>
#include "AlgorithmInfo.h"

/**
 * =========================================================================
 * OOP: ABSTRACTION & INTERFACE (ADITYA'S MODULE)
 * =========================================================================
 * BaseDatabase defines an abstract database interface.
 * Can be implemented by local in-memory databases, SQLite databases, or remote APIs.
 */
class BaseDatabase {
public:
    virtual ~BaseDatabase() = default;

    // Pure virtual method
    virtual std::optional<AlgorithmInfo> findAlgorithm(
        const std::string& algorithmName
    ) const = 0;
};

#endif
