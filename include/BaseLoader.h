#ifndef BASE_LOADER_H
#define BASE_LOADER_H

#include <string>

/**
 * =========================================================================
 * OOP: ABSTRACTION & INTERFACE DESIGN (NAVNEET'S MODULE)
 * =========================================================================
 * BaseLoader is an abstract base class defining the contract for any file
 * loading mechanism (source file loader, binary loader, remote URL loader).
 */
class BaseLoader {
public:
    virtual ~BaseLoader() = default;

    // Pure virtual function making this class an abstract interface
    virtual bool loadFile(
        const std::string& filePath,
        std::string& fileContents,
        std::string& errorMessage
    ) const = 0;
};

#endif
