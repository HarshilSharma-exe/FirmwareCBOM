#include "RiskAnalyzer.h"
#include "RiskRule.h"
#include <vector>
#include <memory>

/**
 * =========================================================================
 * OOP PILLAR 4: RUNTIME POLYMORPHISM (Dynamic Dispatch)
 * =========================================================================
 * This method demonstrates runtime polymorphism:
 * 1. It creates a list of base class pointers: std::vector<std::unique_ptr<RiskRule>>.
 * 2. It loops through them and calls:
 *       rule->applies(...)
 *       rule->evaluate(...)
 * 3. Even though the pointer type is RiskRule*, the program dynamically calls
 *    the overridden function in the derived class (LegacyCipherRule, BrokenHashRule, etc.)
 *    at runtime using the virtual table (vtable).
 */
RiskFinding RiskAnalyzer::assessRisk(
    const CryptoComponent& component,
    const std::optional<AlgorithmInfo>& algorithmInfo
) const {
    RiskFinding finding;
    finding.algorithmName = component.algorithmName;
    finding.sourceFile = component.sourceFile;
    finding.lineNumber = component.lineNumber;

    // Defense-in-depth: If the algorithm is not in the database, flag for manual review
    if (!algorithmInfo.has_value()) {
        finding.severity = "Manual Review";
        finding.reason = "Algorithm '" + component.algorithmName +
                         "' is not recognized in the reference database. Security properties cannot be automatically verified.";
        finding.recommendation = "Conduct a manual cryptographic code audit to determine algorithm specifications, implementation safety, and compliance.";
        return finding;
    }

    // Instantiating derived rule objects polymorphically
    std::vector<std::unique_ptr<RiskRule>> rules;
    rules.push_back(std::make_unique<LegacyCipherRule>());
    rules.push_back(std::make_unique<BrokenHashRule>());
    rules.push_back(std::make_unique<KeyLengthRule>());
    rules.push_back(std::make_unique<SymmetricModeRule>());
    rules.push_back(std::make_unique<StandardAndPostQuantumRule>());

    // Polymorphic invocation (Dynamic dispatch at runtime via vtable)
    for (const auto& rule : rules) {
        if (rule->applies(component, *algorithmInfo)) {
            return rule->evaluate(component, *algorithmInfo); // Calls derived class implementation!
        }
    }

    // Default fallback if no specialized rule applied
    finding.severity = "Manual Review";
    finding.reason = "Algorithm recognized, but contextual security verification is required.";
    finding.recommendation = algorithmInfo->recommendedAction;
    return finding;
}
