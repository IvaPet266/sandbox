#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdint>
#include <iostream>
#include "Position.hpp"
#include "WindowConfig.hpp"
#include "DrawInterface.hpp"

using p_type_t = uint8_t;

constexpr uint8_t RES_W = 100;
constexpr uint8_t RES_H = 100;

enum class particle_t : p_type_t {
    t_void,
    t_monolit,
    t_falling,
    t_levitating
};

class Particle {
public:
    using parsedParticle_t = std::array<particle_t, 4>;
    using p_chank_t        = uint32_t;
private:
    inline static DrawInterface * drawler       = nullptr;
    // WindowConfig window;
    std::array<particle_t, (RES_H * RES_W)> _all {}; 

    inline void beh_falling(size_t index) {
        Position pos = drawler->window_config.hash_to_pos(index);
        Position next_pos = {pos.x, pos.y + 1};
        size_t ind_p1 = drawler->window_config.pos_to_hash(next_pos);

        if (ind_p1 >= _all.size()) {
            _all[index] = particle_t::t_void;
            return;
        }
        if (_all[ind_p1] == particle_t::t_void) {
            _all[index]   = particle_t::t_void;
            _all[ind_p1]  = particle_t::t_falling;
        }
    }
    
    inline void beh_levitating(size_t index) {
        Position pos = drawler->window_config.hash_to_pos(index);
        Position next_pos = {pos.x, pos.y - 1};
        size_t ind_m1 = drawler->window_config.pos_to_hash(next_pos);

        if (ind_m1 < 0) {
            _all[index] = particle_t::t_void;
            return;
        }
        if (_all[ind_m1] == particle_t::t_void) {
            _all[index]   = particle_t::t_void;
            _all[ind_m1]  = particle_t::t_falling;
        }

    }

public:
    void update_all() {
        size_t c = 0;
        for (particle_t p_type : _all) {

            if (p_type == particle_t::t_falling) {
                beh_falling(c);
            } else if (p_type == particle_t::t_levitating) {
                beh_levitating(c);
            } else if (p_type == particle_t::t_void || p_type == particle_t::t_monolit) {}
            c++;
        }
    }
};



inline void cout_bytes(uint8_t number) {
  for (int i = 7; i >= 0; --i) {
    
    uint8_t bit = (number >> i) & 1;
    std::cout << static_cast<int>(bit);
  }
  std::cout << std::endl;
}

