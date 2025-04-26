#include "src/header/ElectionSystem.h"
#include <iostream>

int main() {
    ElectionSystem system;
    int mode = 0;
    std::cout << "\nSelect Mode:\n";
    std::cout << "1. Normal Mode\n";
    std::cout << "2. Demo Mode (auto demonstration)\n";
    std::cout << "Enter your choice: ";
    std::cin >> mode;
    if (mode == 2) {
        system.runDemo();
    } else {
        system.run();
    }
    return 0;
}