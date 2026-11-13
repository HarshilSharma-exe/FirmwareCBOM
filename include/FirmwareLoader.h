#ifndef FIRMWARE_LOADER_H
#define FIRMWARE_LOADER_H

#include <string>
#include "BaseLoader.h"

/**
 * =========================================================================
 * OOP: INHERITANCE (NAVNEET'S MODULE)
 * =========================================================================
 * FirmwareLoader inherits from BaseLoader ('is-a' relationship).
 * It provides the concrete implementation to load files from local disk.
 */
class FirmwareLoader : public BaseLoader {
public:
    bool loadFile(
        const std::string& filePath,
        std::string& fileContents,
        std::string& errorMessage
    ) const override;
};

#endif
