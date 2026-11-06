#ifndef RISK_FINDING_H
#define RISK_FINDING_H

#include <string>


struct RiskFinding {
    std::string algorithmName;     
    std::string severity;          
    std::string reason;           
    std::string recommendation;    
    std::string sourceFile;        
    int lineNumber = 0;            
};

#endif
