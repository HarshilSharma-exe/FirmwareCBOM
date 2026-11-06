#ifndef BASE_REPORT_GENERATOR_H
#define BASE_REPORT_GENERATOR_H

#include <string>
#include <vector>
#include "CryptoComponent.h"
#include "RiskFinding.h"

class BaseReportGenerator {
public:
    virtual ~BaseReportGenerator() = default;

    // Pure virtual method
    virtual std::string generate(
        const std::vector<CryptoComponent>& components,
        const std::vector<RiskFinding>& findings
    ) const = 0;
};

#endif
