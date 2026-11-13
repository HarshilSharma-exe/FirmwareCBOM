#include "FirmwareLoader.h"
#include <fstream>
#include <sstream>

/**
 * =========================================================================
 * OOP PILLAR 1: ENCAPSULATION
 * =========================================================================
 * FirmwareLoader encapsulates all file reading operations.
 * Callers simply call loadFile() without worrying about ifstream streams or buffers.
 */
bool FirmwareLoader::loadFile(
    const std::string& filePath,
    std::string& fileContents,
    std::string& errorMessage
) const {
    fileContents.clear();
    errorMessage.clear();

    std::ifstream file(filePath, std::ios::in);
    if (!file.is_open()) {
        errorMessage = "Failed to open file '" + filePath + "': file does not exist or permission denied.";
        return false;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    fileContents = buffer.str();

    file.close();
    return true;
}
