#ifndef CBOM_GENERATOR_H
#define CBOM_GENERATOR_H

#include <string>
#include <vector>
#include "BaseReportGenerator.h"
#include "CryptoComponent.h"
#include "RiskFinding.h"

class CBOMGenerator : public BaseReportGenerator {
public:
    // Overriding the base class polymorphic interface
    std::string generate(
        const std::vector<CryptoComponent>& components,
        const std::vector<RiskFinding>& findings
    ) const override;

    // Backward-compatible method matching original blueprint interface
    std::string generateJson(
        const std::vector<CryptoComponent>& components,
        const std::vector<RiskFinding>& findings
    ) const;
};

#endif
