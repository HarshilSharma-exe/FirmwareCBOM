#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "FirmwareLoader.h"
#include "CryptoScanner.h"
#include "CryptoDatabase.h"
#include "RiskAnalyzer.h"
#include "CBOMGenerator.h"

/**
 * =========================================================================
 * PIPELINE COORDINATION (main.cpp)
 * =========================================================================
 * Coordinates the full Cryptographic Bill of Materials (CBOM) pipeline.
 *
 * OOP Principles Illustrated:
 *  - High-level orchestration through Abstraction.
 *  - Objects collaborate cleanly without exposing internal details.
 */
int main(int argc, char* argv[]) {
    // Step 1: Create instances of the modular pipeline classes
    FirmwareLoader loader;
    CryptoScanner scanner;
    CryptoDatabase database;
    RiskAnalyzer analyzer;
    CBOMGenerator generator;

    std::string targetFile = "sample.cpp";
    if (argc > 1) {
        targetFile = argv[1];
    }

    // Step 2: Load the source code file safely
    std::string sourceCode, errorMessage;
    if (!loader.loadFile(targetFile, sourceCode, errorMessage)) {
        std::cerr << "Error: " << errorMessage << '\n';
        return 1;
    }

    // Step 3: Scan the source text to detect cryptographic references
    auto components = scanner.scan(sourceCode, targetFile);

    // Step 4: For each detected component, query database and evaluate risks
    std::vector<RiskFinding> findings;
    for (const CryptoComponent& component : components) {
        auto info = database.findAlgorithm(component.algorithmName);
        findings.push_back(analyzer.assessRisk(component, info));
    }

    // Step 5: Generate the structured JSON report
    std::string report = generator.generateJson(components, findings);

    // Step 6: Save the report to cbom_report.json
    std::ofstream outputFile("cbom_report.json");
    if (!outputFile) {
        std::cerr << "Could not create report file.\n";
        return 1;
    }
    outputFile << report;
    outputFile.close();

    // Step 7: Print clean summary to terminal
    std::cout << "Scan completed.\n";
    std::cout << "Components detected: " << components.size() << '\n';
    std::cout << "Report saved to cbom_report.json\n";

    return 0;
}
