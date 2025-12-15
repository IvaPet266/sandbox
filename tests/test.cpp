#include <array>
#include <cstdlib>
#include <iostream>
#include "../include/Position.hpp"

#define TEST_COUNT 5
#define PARAM_COUNT 4

int func(int a, int b) {
    return a / b;
};

int main() {
    std::array<std::array<int, PARAM_COUNT>, TEST_COUNT> tests = {{
        {4,  2, 2, 5},
        {8,  4, 2, 5},
        {6,  2, 1, 5},
        {10, 2, 2, 5},
        {40, 5, 7, 5}
    }};

    std::cout << "Running tests...\n";

    bool all_ok = true;
    
    
    std::cout << (all_ok ? "All tests passed\n" : "Some tests failed\n");
    return EXIT_SUCCESS;
};
