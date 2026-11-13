#include <iostream>
#include <cassert>
#include <string>
#include <memory>
#include "BaseLoader.h"
#include "FirmwareLoader.h"

void testLoaderSuccess() {
    std::cout << "[RUNNING] testLoaderSuccess...\n";
    // Polymorphic instantiation via base class pointer
    std::unique_ptr<BaseLoader> loader = std::make_unique<FirmwareLoader>();

    std::string contents, error;
    bool success = loader->loadFile("sample.cpp", contents, error);

    assert(success == true);
    assert(!contents.empty());
    assert(error.empty());
    std::cout << "[PASSED] testLoaderSuccess\n";
}

void testLoaderMissingFile() {
    std::cout << "[RUNNING] testLoaderMissingFile...\n";
    std::unique_ptr<BaseLoader> loader = std::make_unique<FirmwareLoader>();

    std::string contents, error;
    bool success = loader->loadFile("non_existent_file.xyz", contents, error);

    // Missing file should gracefully return false and give clear error message
    assert(success == false);
    assert(contents.empty());
    assert(!error.empty());
    std::cout << "[PASSED] testLoaderMissingFile\n";
}

int main() {
    std::cout << "========================================\n";
    std::cout << "Running FirmwareLoader Tests (Navneet)\n";
    std::cout << "========================================\n";
    testLoaderSuccess();
    testLoaderMissingFile();
    std::cout << "All FirmwareLoader tests passed successfully!\n";
    return 0;
}
