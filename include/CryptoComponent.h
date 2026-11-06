#ifndef CRYPTO_COMPONENT_H
#define CRYPTO_COMPONENT_H

#include <optional>
#include <string>

struct CryptoComponent {
    std::string algorithmName;     
    std::string category;         
    std::string usage;            

    std::optional<int> keySizeBits;

    std::string sourceFile;        
    int lineNumber = 0;            
    std::string evidence;         
};

#endif
