// Simple non-cryptographic utility
#include <iostream>

int calculateChecksum(int a, int b) {
    return a + b;
}

int main() {
    std::cout << "Sum: " << calculateChecksum(10, 20) << "\n";
    return 0;
}
