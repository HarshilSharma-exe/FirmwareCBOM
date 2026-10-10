#ifndef CBOM_GENERATOR_H
#define CBOM_GENERATOR_H

#include <string>
#include <vector>

#include "CryptoComponent.h"

// CBOMGenerator turns a list of detected CryptoComponent objects into
// output a human (or another tool) can use:
//   - a JSON file  (the CBOM itself)
//   - a plain-text report
// It only formats data. It does not scan files and does not judge risk.
class CBOMGenerator {
private:
    // Makes text safe to place inside a JSON string (handles " \ and newlines).
    static std::string escapeJson(const std::string& text);

public:
    // Builds the CBOM as a JSON string.
    std::string toJSON(const std::vector<CryptoComponent>& components,
                       const std::string& firmwareName) const;

    // Builds a readable text report, including a count of components per type.
    std::string toTextReport(const std::vector<CryptoComponent>& components,
                             const std::string& firmwareName) const;

    // Saves text to a file. Throws std::runtime_error if the file cannot be written.
    void writeToFile(const std::string& path, const std::string& content) const;
};

#endif
