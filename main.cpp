// FirmwareCBOM - scanner + CBOM generator
//
// Run from the project root folder (so the sample paths below are found).
//
// Usage:
//   ./firmwarecbom                      -> scans the 4 sample firmware files
//   ./firmwarecbom file1.cpp file2.cpp  -> scans the files you give
//
// Output:
//   cbom.json   - the Cryptographic Bill of Materials
//   report.txt  - a readable report

#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "CBOMGenerator.h"
#include "CryptoComponent.h"
#include "CryptoScanner.h"

int main(int argc, char* argv[]) {
    std::vector<std::string> files;
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) files.push_back(argv[i]);
    } else {
        files = {"firmware_samples/sensor.cpp",
                 "firmware_samples/communication.cpp",
                 "firmware_samples/authentication.cpp",
                 "firmware_samples/storage.cpp"};
    }

    CryptoScanner scanner;
    CBOMGenerator generator;
    std::vector<CryptoComponent> inventory;

    std::cout << "=== FirmwareCBOM: Cryptographic Inventory ===\n\n";

    // Step 1: scan every file and collect the findings
    for (const std::string& file : files) {
        try {
            std::vector<CryptoComponent> found = scanner.scanFile(file);
            std::cout << "Scanned " << file << " -> " << found.size()
                      << " component(s)\n";
            inventory.insert(inventory.end(), found.begin(), found.end());
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }

    // Step 2: generate the CBOM and the report
    const std::string firmwareName = "SimulatedFirmware";
    try {
        generator.writeToFile("cbom.json", generator.toJSON(inventory, firmwareName));
        generator.writeToFile("report.txt", generator.toTextReport(inventory, firmwareName));
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    std::cout << "\nTotal components found: " << inventory.size() << "\n";
    std::cout << "Written: cbom.json, report.txt\n";
    return 0;
}
