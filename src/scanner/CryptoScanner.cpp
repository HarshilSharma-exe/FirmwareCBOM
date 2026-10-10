#include "CryptoScanner.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>

using namespace std;

namespace fs = filesystem;

CryptoScanner::CryptoScanner(const CryptoDatabase& db) : database(db) {}

// This function checks the line and finds which cryptographic algorithm is used
string CryptoScanner::detectAlgorithm(const string& line) const {
    
    // Stores the keyword and its standard algorithm name
    struct KeywordMap { 
        string keyword; 
        string canonical; 
    };

    // List of cryptographic keywords to search for
    static const vector<KeywordMap> keywords = {
        {"AES256", "AES-256"}, 
        {"AES_256", "AES-256"}, 
        {"AES-256", "AES-256"},

        {"AES128", "AES-128"}, 
        {"AES_128", "AES-128"}, 
        {"AES-128", "AES-128"},

        {"RSA2048", "RSA-2048"}, 
        {"RSA_2048", "RSA-2048"}, 
        {"RSA-2048", "RSA-2048"},

        {"RSA3072", "RSA-3072"}, 
        {"RSA_3072", "RSA-3072"}, 
        {"RSA-3072", "RSA-3072"},

        {"RSA", "RSA-2048"}, // If RSA size is not given, use RSA-2048

        {"ECDSA", "ECDSA"},

        {"SHA256", "SHA-256"}, 
        {"SHA_256", "SHA-256"}, 
        {"SHA-256", "SHA-256"},

        {"SHA1", "SHA-1"}, 
        {"SHA_1", "SHA-1"}, 
        {"SHA-1", "SHA-1"},

        {"MD5", "MD5"},
        {"DES", "DES"},
    };

    // Check each keyword in the given line
    for (const auto& k : keywords) {

        // If a keyword is found, return its standard name
        if (line.find(k.keyword) != string::npos) {
            return k.canonical;
        }
    }

    // Return empty string if no algorithm is found
    return "";
}

vector<CryptoComponent> CryptoScanner::scanFile(const string& filename) const {

    // Stores all algorithms found in the file
    vector<CryptoComponent> found;

    // Open the file
    ifstream file(filename);

    // Check if the file was opened successfully
    if (!file.is_open()) {
        cerr << "Warning: could not open file " << filename << endl;
        return found;
    }

    string line;

    // Read the file one line at a time
    while (getline(file, line)) {

        // Check the current line for a cryptographic algorithm
        string algorithm = detectAlgorithm(line);

        // If an algorithm is found
        if (!algorithm.empty()) {

            // Check whether the algorithm is present in the database
            string type = database.isKnown(algorithm)
                                    ? database.getType(algorithm)
                                    : "unknown";

            // Store the algorithm, its type, and the file name
            found.emplace_back(algorithm, type, filename);
        }
    }

    // Return all algorithms found in the file
    return found;
}

vector<CryptoComponent> CryptoScanner::scanDirectory(const string& directoryPath) const {

    // Stores results from all files in the directory
    vector<CryptoComponent> allFound;

    // Check whether the directory exists
    if (!fs::exists(directoryPath) || !fs::is_directory(directoryPath)) {

        cerr << "Warning: directory not found: " << directoryPath << endl;
        return allFound;
    }

    // Go through every item in the directory
    for (const auto& entry : fs::directory_iterator(directoryPath)) {

        // Process only normal files
        if (entry.is_regular_file()) {

            // Scan the current file
            vector<CryptoComponent> fileResults = scanFile(entry.path().string());

            // Add the results to the main result list
            allFound.insert(
                allFound.end(),
                fileResults.begin(),
                fileResults.end()
            );
        }
    }

    // Return all detected algorithms
    return allFound;
}
