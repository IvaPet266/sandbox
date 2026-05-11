#include <chrono>
#include <functional>

#include "print/terminal.hpp"


using namespace std::chrono;

#pragma once


class TimeManager {
private:
    nanoseconds STEP;
    time_point<std::chrono::steady_clock> st_tp;
    time_point<std::chrono::steady_clock> global_tp;
    std::function<void()> task;
    int frames = 0;
public:
    TimeManager (nanoseconds step, std::function<void()> func) : 
        STEP(step), 
        task(func), 
        st_tp(steady_clock::now()), 
        global_tp(steady_clock::now()) 
    {};
    
    void tick() {
        auto frame_tp = steady_clock::now();

        auto delta = frame_tp - st_tp;
        auto gl_delta = frame_tp - global_tp;
        if (delta >= STEP) {
            task();
            frames++;
            st_tp = steady_clock::now();
        };
        if (gl_delta >= 1s) {
            std::cout << frames << " FPS" << std::endl;
            frames = 0;
            global_tp = steady_clock::now();
        }
    };


};

