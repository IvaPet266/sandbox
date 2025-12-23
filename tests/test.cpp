#include <array>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <vector>
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
    bool all_ok = true;

    std::cout << "Running tests...\n";
    std::vector<Position> res;
    for (size_t i = 0; i < tests.size(); i++) {
        std::cout << "test" << i+1 << std::endl;
        res = Position::interpolate(Position(tests[i][0], tests[i][1]), Position(tests[i][2], tests[i][3]));
        for (size_t e = 0; e < res.size(); e++) { // проверка на границы
            if (tests[i][0] - tests[i][2] > 0) {
                if (res[e].x > tests[i][0] || res[e].x < tests[i][2]) {
                    std::cerr << "out of range 1: " << res[e].x << std::endl;
                    all_ok = false;
                }
            } else {
                if (res[e].x < tests[i][0] || res[e].x > tests[i][2]) {
                    std::cerr << "out of range 2: " << res[e].x << std::endl;
                    all_ok = false;
                }
            }
            if (tests[i][1] - tests[i][3] > 0) {
                if (res[e].x > tests[i][1] || res[e].x < tests[i][3]) {
                    std::cerr << "out of range 3: " << res[e].x << std::endl;
                    all_ok = false;
                }
            } else {
                if (res[e].x < tests[i][1] || res[e].x > tests[i][3]) {
                    std::cerr << "out of range 4: " << res[e].x << std::endl;
                    all_ok = false;
                }
            }
                int dx = std::abs(tests[i][0] - res[e].x);
                int dy = std::abs(tests[i][1] - res[e].y);
                all_ok = dx <= 1 && dy <= 1;
            }
        }
        std::cout << "=========" << std::endl;    
    
    std::cout << (all_ok ? "All tests passed\n" : "Some tests failed\n");
    return EXIT_SUCCESS;
};
