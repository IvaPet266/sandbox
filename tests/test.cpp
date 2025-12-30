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
    Position    start_pos;
    Position    target_pos;
    int         steps_amount = 0;
    std::string name         = "first";

    void error_output(Position& current_pos) {
        std::cerr << "test " << name << " failed\n";
        std::cerr << "problem occured in position :: " << current_pos.to_string() << "\n";
    }
};

int main() {
    std::vector<PosData> tests = {
        PosData{4,  2, 3,  5, 3,  "first"  },
        PosData{8,  4, 2,  5, 6,  "second" },
        PosData{6,  2, 1,  5, 5,  "third"  },
        PosData{10, 2, 2,  5, 8,  "fourth" },
        PosData{30, 5, 7,  5, 23, "fifth"  },
        PosData{40, 5, 40, 5, 1,  "sixth"  },
        PosData{4,  2, 8,  4, 4,  "seventh"},
        PosData{3,  5, 8,  4, 5,  "eighth" },
        PosData{4,  2, 2,  5, 3,  "ninth"  },
        PosData{3,  5, 2,  5, 1,  "tenth"  },
    };
    bool all_ok = true;

    std::cout << "Running tests...\n";
    for (auto& case_ : tests) {
        int step_counter = 0;
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
            step_counter++;
            std::cout << cur_pos.to_string() << std::endl;
        } while (not (cur_pos.x == case_.target_pos.x && cur_pos.y == case_.target_pos.y));
        if (step_counter == case_.steps_amount) {
            std::cout << "right amount of steps: " << step_counter << "\n";
        } else { 
            std::cerr << "steps amount is not correct: " << step_counter << " :: " << case_.steps_amount << "\n";
            all_ok = false; 
        };
        std::cout << "=========" << std::endl;    
    };

    
    std::cout << (all_ok ? "All tests passed\n" : "Some tests failed\n");
    return EXIT_SUCCESS;
};
