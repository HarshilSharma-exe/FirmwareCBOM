#ifndef CBOM_GENERATOR_H
#define CBOM_GENERATOR_H

#include <string>
#include <vector>
#include "CryptoComponent.h"
#include "RiskFinding.h"

class CBOMGenerator {
public:
    std::string generateJson(const std::vector<CryptoComponent>& components, const std::vector<RiskFinding>& findings) const;
};

#endif