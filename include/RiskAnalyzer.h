#ifndef RISK_ANALYZER_H
#define RISK_ANALYZER_H

#include <optional>
#include "CryptoComponent.h"
#include "AlgorithmInfo.h"
#include "RiskFinding.h"

/**
 * Class responsible for assessing risks of detected cryptographic components.
 * OOP Concept: Abstraction - Exposes a clean 'assessRisk' method.
 * Internally, it leverages runtime polymorphism via RiskRule derived classes.
 */
class RiskAnalyzer {
public:
    RiskFinding assessRisk(
        const CryptoComponent& component,
        const std::optional<AlgorithmInfo>& algorithmInfo
    ) const;
};

#endif
