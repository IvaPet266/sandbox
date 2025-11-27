#include "SDL2/SDL_stdinc.h"

#include <Timer.hpp>


#define PART_TYPES_AMOUNT 3
#define SPEEDS_AMOUNT 3

#pragma once


class Control {
private:
    bool  run           = true;
    bool  lctrl_pressed = false;
    bool  rctrl_pressed = false;
    bool  space_pressed = false;
    bool  shift_pressed = false;
    bool  lmb_pressed   = false;
    bool  rmb_pressed   = false;
    bool  r_pressed     = false;
    int   particle_code = 0;
    Uint8 speed         = 1;
public:
    void set_run(bool new_flag) {
        run = new_flag;
        std::cout << "run -> " << run << std::endl;
    }
    bool get_run() const {
        return run;
    }

    void set_particle_code(int new_code) {
        particle_code = new_code;
        std::cout<< "particle_code -> " << particle_code << std::endl;
    }
    int get_particle_code() const {
        return particle_code;
    }

    void set_speed(Uint8 new_speed) {
        speed = new_speed;
        std::cout<< "speed -> " << speed << std::endl;
    }
    Uint8 get_speed() const {
        return speed;
    }

    void set_lctrl(bool new_flag) {
        lctrl_pressed = new_flag;
        std::cout<< "lctrl -> " << lctrl_pressed << std::endl;
    }
    bool get_lctrl() const {
        return lctrl_pressed;
    }

    void set_rctrl(bool new_flag) {
        rctrl_pressed = new_flag;
        std::cout<< "rctrl -> " << rctrl_pressed << std::endl;
    }
    bool get_rctrl() const {
        return lctrl_pressed;
    }
    
    void set_space(bool new_flag) {
        space_pressed = new_flag;
        std::cout<< "space -> " << space_pressed << std::endl;
    }
    bool get_space() const {
        return space_pressed;
    }

    void set_shift(bool new_flag) {
        shift_pressed = new_flag;
        std::cout<< "shift -> " << shift_pressed << std::endl;
    }
    bool get_shift() const {
        return shift_pressed;
    }

    void set_lmb(bool new_flag) {
        lmb_pressed = new_flag;
        std::cout<< "lmb -> " << lmb_pressed << std::endl;
    }
    bool get_lmb() const {
        return lmb_pressed;
    }

    void set_rmb(bool new_flag) {
        rmb_pressed = new_flag;
        std::cout<< "rmb -> " << rmb_pressed << std::endl;
    }
    bool get_rmb() const {
        return rmb_pressed;
    }

    void set_r(bool new_flag) {
        r_pressed = new_flag;
        std::cout<< "r -> " << r_pressed << std::endl;
    }
    bool get_r() const {

        return r_pressed;
    }

    
    
};

Control control = Control();