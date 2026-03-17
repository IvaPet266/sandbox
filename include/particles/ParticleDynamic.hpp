#include <array>
#include <cstdint>
#include <cstdint>
#include <iostream>

using p_type_t = uint8_t;

enum class particle_t : p_type_t {
    t_void,
    t_monolit,
    t_falling,
    t_levitating
};




class Game {
public:
    using parsedParticle_t = std::array<particle_t, 4>;
    using p_chank_t        = uint32_t;
private:
    // WindowConfig window;
    std::array<p_chank_t, 100*100> particles {0b101010011001}; // каждый индекс -- координата. array сжимает в себе 4 чанка, где на
                                                                   // кодирование типа приходится 3 бита (всего 12)

    parsedParticle_t ParseParticleT(p_chank_t p_chank)
    {
        parsedParticle_t result;
    
        constexpr uint32_t MASK = 0b111;
    
        for (p_type_t i = 0; i < 4; ++i)
        {
            p_type_t type = (p_chank >> (i * 3)) & MASK;
            result[i] = static_cast<particle_t>(type);
        }
        return result;
    }
public:
    void update() {
        for (p_chank_t p_chank : particles) {

            parsedParticle_t chank = ParseParticleT(p_chank);
            for (particle_t p_type : chank) {
                if (p_type == particle_t::t_falling) {
                
                } else if (p_type == particle_t::t_levitating) {
    
                }
            }
        }
    }
};