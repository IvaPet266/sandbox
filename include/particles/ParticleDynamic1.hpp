#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <vector>

#include "Position.hpp"
#include "WindowConfig.hpp"
#include "DrawInterface.hpp"
#include "control.hpp"

#pragma once

const uint8_t RES_W = 100;
const uint8_t RES_H = 100;


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


class Particle {
public:
    using parsedParticle_t = std::vector<particle_t>;
    using p_chank_t        = uint32_t;
    inline static parsedParticle_t _all {}; 
private:
    inline static DrawInterface*   drawler = nullptr;
    // WindowConfig window;
    

    inline static void set_changed(size_t index, size_t ind_n1, particle_t new_state) {
        if (_all[ind_n1] == particle_t::t_void) {
            _all[index]   = particle_t::t_void;
            _all[ind_n1]  = parse_particle(new_state, particle_t::t_changed, bitwise_operations_t::t_or);
        } else return;
    };

    inline static void beh_falling(size_t index) {
        Position pos = drawler->window_config.hash_to_pos(index);
        Position next_pos = {pos.x, pos.y + 1};
        size_t ind_p1 = drawler->window_config.pos_to_hash(next_pos);

        if (ind_p1 >= _all.size()) {
            _all[index] = particle_t::t_void;
            return;
        }
        set_changed(index, ind_p1, particle_t::t_falling);
    };
    
    inline static void beh_levitating(size_t index) {
        Position pos = drawler->window_config.hash_to_pos(index);
        Position next_pos = {pos.x, pos.y - 1};
        size_t ind_m1 = drawler->window_config.pos_to_hash(next_pos);

        if (ind_m1 < 0) {
            _all[index] = particle_t::t_void;
            return;
        }
        set_changed(index, ind_m1, particle_t::t_levitating);
    };

public:

    Particle() {
        _all.resize(drawler->window_config.get_res_area(), particle_t::t_void);
    };

    static void update_all() {
        size_t c = 0;
        for (particle_t p_type : _all) {
            const bool changed = static_cast<uint8_t>(p_type) & static_cast<uint8_t>(particle_t::t_changed);
            if (!changed) {
                p_type = static_cast<particle_t>((static_cast<uint8_t>(p_type) >> 1) << 1);
                
                if (p_type == particle_t::t_void || p_type == particle_t::t_monolit) {
                } else {
                    if (p_type == particle_t::t_falling) {
                        beh_falling(c);
                    } else if (p_type == particle_t::t_levitating) {
                        beh_levitating(c);
                    } else {
                        std::cerr << "Unknown particle type: " << static_cast<uint8_t>(p_type) << std::endl;
                    }
                }
            } else {
                _all[c] = parse_particle(_all[c], particle_t::t_changed, bitwise_operations_t::t_xor);
            }
            c++;
        }
    };

    inline static bool create_new(Position pos, particle_t type) {
        size_t index = drawler->window_config.pos_to_hash(pos);
        if (index >= _all.size() || _all[index] != particle_t::t_void) {
            return false;
        }
        _all[index] = type;
        return true;
    };

    inline static size_t get_all_size() {
        return _all.size();
    };

    static void clear() {
        //TODO 
        Uint16 s = _all.size();
        auto st_time = std::chrono::high_resolution_clock().now();
        _all.clear();
        drawler->clear_buffer();

        print("clear");
        auto end_time = std::chrono::high_resolution_clock().now();
        auto dur = end_time- st_time; //std::chrono::duration_cast<std::chrono::microseconds>(end_time - st_time);
        print("clear time", dur);
        print("particles cleared", s);
    };

    static void init(WindowConfig * wind_config, DrawInterface * drawler) {
    
        #if DEBUG
        if ( not wind_config ) throw std::invalid_argument("Particle :: init :: nullptr WindowConfig");
        #endif

        // Particle::window_config = wind_config;
        Particle::drawler       = drawler;
        // _all.reserve(window_config->get_res_area() / 2);
    };
};




