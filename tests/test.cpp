#include <array>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "../include/Position.hpp"

#define TEST_COUNT 5
#define PARAM_COUNT 4

struct PosData {
    Position start_pos;
    Position target_pos;
    std::string name = "first";

    void error_output(Position& current_pos) {
        std::cerr << "test " << name << " failed\n";
        std::cerr << "problem occured in position :: " << current_pos.to_string() << "\n";
    }
};

int main() {
    std::vector<PosData> tests = {
        PosData{4,  2, 2, 5, "first" },
        PosData{8,  4, 2, 5, "second"},
        PosData{6,  2, 1, 5, "third" },
        PosData{10, 2, 2, 5, "fourth"},
        PosData{30, 5, 7, 5, "fifth" },
        PosData{40, 5, 40, 5, "sixth" },
    };
    bool all_ok = true;

    std::cout << "Running tests...\n";
    for (auto& case_ : tests) {
        std::cout << "running " << case_.name << " test\n";
        Position cur_pos = case_.start_pos;
        do {
            Position new_pos = Position::interpolate(cur_pos, case_.target_pos);
            if (
                std::abs(cur_pos.x - new_pos.x) > 1 ||
                std::abs(cur_pos.y - new_pos.y) > 1
            ) {
                case_.error_output(cur_pos);
                break;
            };
            cur_pos = new_pos;
            std::cout << cur_pos.to_string() << std::endl;
        } while (cur_pos.x != case_.target_pos.x && cur_pos.y != case_.target_pos.y);
    };

    std::cout << "=========" << std::endl;    
    
    std::cout << (all_ok ? "All tests passed\n" : "Some tests failed\n");
    return EXIT_SUCCESS;
};
