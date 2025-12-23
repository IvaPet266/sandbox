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
    for (auto it = tests.begin(); it != tests.end(); it++) {
        Position res = Position::interpolate(Position{(*it)[0], (*it)[1]}, Position{(*it)[2], (*it)[3]});
        std::vector<Position> res_list = {Position{(*it)[0], (*it)[1]}};

        while (res.x != (*it)[2] && res.y != (*it)[3]) {
            int dx = std::abs(res.x - res_list[res_list.size()-1].x);
            int dy = std::abs(res.y - res_list[res_list.size()-1].y);

            if (dx > 1 || dy > 1) {
                std::cout << "out of range 1" << std::endl;
                all_ok = false;
                break;
            }

            res = Position::interpolate(Position{res.x, res.y}, Position{(*it)[2], (*it)[3]});
            res_list.push_back(res);
        };
        for (auto it = res_list.begin(); it < res_list.end(); it++) {
            std::cout << it->to_string() << std::endl;
        }
    }

    std::cout << "=========" << std::endl;    
    
    std::cout << (all_ok ? "All tests passed\n" : "Some tests failed\n");
    return EXIT_SUCCESS;
};
