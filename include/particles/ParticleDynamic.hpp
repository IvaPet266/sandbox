#include <array>
#include <cstdint>
#include <cstdint>
#include <iostream>


enum class particle_t : uint8_t {
    t_void,
    t_monolit,
    t_falling,
    t_levitating
};




class Game {
public:
    using parsedParticle_t = std::array<uint8_t, 3>;
    using p_chank_t        = uint32_t;
private:
    // WindowConfig window;
    std::array<p_chank_t, 100*100> particles {0b101010011001}; // каждый индекс -- координата. array сжимает в себе 4 чанка, где на
                                                                   // кодирование типа приходится 3 бита (всего 12)

    parsedParticle_t ParseParticleT(p_chank_t p_chank)
    {
        parsedParticle_t result;
    
        constexpr p_chank_t MASK = 0b111;
    
        for (uint8_t i = 0; i < 4; ++i)
        {
            uint8_t type = (p_chank >> (i * 3)) & MASK;
            result[i] = type;
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