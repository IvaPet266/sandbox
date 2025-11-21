#include <chrono>
#include <functional>
#include <iostream>

using namespace std::chrono;


class TimeManager {
private:
    milliseconds STEP;
    time_point<std::chrono::steady_clock> st_tp;
    std::function<void()> task;
public:
    TimeManager (milliseconds step, std::function<void()> func) : STEP(step), task(func), st_tp(steady_clock::now()) {};
    
    void tick() {
        auto frame_tp = steady_clock::now();

        auto delta = frame_tp - st_tp;
        if (delta >= STEP) {
            std::cout << "tick" << std::endl;
            task();
            st_tp = steady_clock::now();
        };
    };
};

