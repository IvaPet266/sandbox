#include <array>
#include <cstdlib>
#include <iostream>

#define TEST_COUNT 5
#define PARAM_COUNT 3

int func(int a, int b) {
    return a / b;
};

int main() {
    std::array<std::array<int, PARAM_COUNT>, TEST_COUNT> tests = {{
        {4,  2, 2},
        {8,  4, 2},
        {6,  2, 1},
        {10, 2, 2},
        {40, 5, 7}
    }};

    std::cout << "Running tests...\n";

    bool all_ok = true;
    for (size_t i = 0; i < TEST_COUNT; ++i) {
        int result = func(tests[i][0], tests[i][1]);
        bool ok = (result == tests[i][2]);

        std::cout << "TEST " << i + 1 << " -> " << ok << '\n';

        if (!ok) {
            all_ok = false;
            std::cout << "  expected: " << tests[i][2]
                      << ", got: " << result << '\n';
        };
    };

    std::cout << (all_ok ? "All tests passed\n" : "Some tests failed\n");
    return EXIT_SUCCESS;
};
