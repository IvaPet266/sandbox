#include "SDL2/SDL_stdinc.h"

#include "defines.hpp"
#include <Timer.hpp>
#include <cstdint>

#include "C:\Users\shosh\vscode_projects\cpp\1\tools\tools"


#pragma once

enum class bitwise_operations_t : uint8_t {
    t_and = 0,
    t_or  = 1,
    t_xor = 2
};


enum class particle_t : uint8_t {
    t_void        = 0,
    t_changed     = 1,
    t_monolit     = 2,
    t_falling     = 4,
    t_levitating  = 6, 
    t_living_fast = 8,

    t_update      = 128 // - 10000000
};

inline static particle_t parse_particle(particle_t p, const particle_t bit, bitwise_operations_t op = bitwise_operations_t::t_or) {
    switch (op) {
        case bitwise_operations_t::t_and:
            return static_cast<particle_t>(static_cast<uint8_t>(p) & static_cast<uint8_t>(bit));
        case bitwise_operations_t::t_or:
            return static_cast<particle_t>(static_cast<uint8_t>(p) | static_cast<uint8_t>(bit));
        case bitwise_operations_t::t_xor:
            return static_cast<particle_t>(static_cast<uint8_t>(p) ^ static_cast<uint8_t>(bit));
        default:
            return p;
    }
};

class Control {
private:
    particle_t particle_code = particle_t::t_void;
    bool       run           = true;
    bool       lctrl_pressed = false;
    bool       rctrl_pressed = false;
    bool       space_pressed = false;
    bool       shift_pressed = false;
    bool       lmb_pressed   = false;
    bool       rmb_pressed   = false;
    bool       r_pressed     = false;
    int        speed         = 1;
public:
    
    void set_run(bool new_flag) {
        run = new_flag;
        std::cout << "run -> " << run << std::endl;
    }
    bool get_run() const {
        return run;
    }

    void set_particle_code(particle_t new_code) {
        particle_code = new_code;
        std::cout<< "particle_code -> " << static_cast<uint8_t>(particle_code) << std::endl;
    }
    particle_t get_particle_code() const {
        return particle_code;
    }

    void set_speed(int new_speed) {
        speed = new_speed;
        std::cout<< "speed -> " << speed << std::endl;
    }
    int get_speed() {
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