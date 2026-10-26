#ifndef CRYPTOSCANNER_H
#define CRYPTOSCANNER_H

#include <iostream>
#include <string>
#include <vector>
#include "../models/CryptoComponent.h"
#include "../database/CryptoDatabase.h"

using namespace std;

class CryptoScanner {
private:
    const CryptoDatabase& database;

    string detectAlgorithm(string line) const;

public:
    CryptoScanner(const CryptoDatabase& db);

    vector<CryptoComponent> scanFile(string filename) const;

    vector<CryptoComponent> scanDirectory(string directoryPath) const;
};

#endif
