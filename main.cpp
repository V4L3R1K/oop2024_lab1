#include "lab1.h"
#include <iostream>

using namespace lab1;

int main() {
    try {
        loop();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}