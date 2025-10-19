#include "SDL2/SDL_stdinc.h"
#include "WindowConfig.hpp"
#include <DrawInterface.hpp>
#include <functional>
#include <particles/ParticleStatic.hpp>
#include <EventTriggers.hpp>
#include <SDL2/SDL_timer.h>

#include <memory>
#include <map>
#include <vector>
#include <chrono>


using namespace std::chrono;


class TimeManager {
protected:
    std::map<int, std::function<void()>> tasks;
    std::map<int, std::function<bool()>> ret_tasks;

    std::chrono::steady_clock SteadyClock = std::chrono::steady_clock();
    
    std::chrono::time_point<std::chrono::steady_clock> start_time;
    Uint32 query_size = 10;

    bool ticking = true;
public:

    void operator() (int intervalMs, std::function<void()> & new_task) {

        auto [ it, inserted ] = tasks.emplace(new_task);
        // return inserted;
    }

    void operator() (int intervalMs, std::function<bool()> & new_task) {

        auto [ it, inserted ] = ret_tasks.emplace(new_task);
        // return inserted;
    }

    void set_ticking(bool new_instance) {
        ticking = new_instance;
    }

    void start_ticking() {
        start_time = SteadyClock.now();
        Uint8 frame_count = 0;
        while (ticking) {
            
            auto frame_time = SteadyClock.now();
            Uint8 elapsed_time = std::chrono::duration_cast<milliseconds>(frame_time - start_time).count();
            
            if (elapsed_time % 16 == 0) {
                frame_count++;
                auto current_task = tasks.find(16)->second;
                current_task();
                SDL_Delay(1); // — снижение нагрузки на CPU.
            } else if (elapsed_time >= 1000) {
                print("FPS:", frame_count);
                frame_count = 0;
                start_time = SteadyClock.now();
            } else {
                auto current_task = tasks.find(-1)->second;
                current_task();

                auto current_ret_task = ret_tasks.find(-1)->second;
                ticking = not current_ret_task();
            }
        }
        return;
    }
    
};
