


#include <cstdint>
#include <limits>
#include <iostream>
#include <ostream>

bool check_bit(uint8_t byte, int position) {

    return !((byte >> position) & 1);
}


inline void cout_bytes(uint8_t number) {
  for (int i = 7; i >= 0; --i) {
    
    uint8_t bit = (number >> i) & 1;
    std::cout << static_cast<int>(bit);
  }
  std::cout << std::endl;
}

enum class p : uint8_t {
    t_void       = 0,
    t_changed    = 1,
    t_monolit    = 2,
    t_falling    = 4,
    t_levitating = 6
};


int main() {

    // for (uint8_t n = 0; n < std::numeric_limits<uint8_t>::max(); n++) {
    //     if (check_bit(n,0)) {
    //         std::cout << static_cast<int>(n) << " has 0" << std::endl;
    //     }    
    // }

    p n = p::t_monolit;
    p n1 = p::t_falling;
    p n2 = static_cast<p>(static_cast<uint8_t>(n1) | static_cast<uint8_t>(p::t_changed));
    p n3 = static_cast<p>(static_cast<uint8_t>(n2) ^ static_cast<uint8_t>(p::t_changed));

    // cout_bytes(static_cast<uint8_t>(n));
    // cout_bytes(static_cast<uint8_t>(n) | static_cast<uint8_t>(p::t_changed)); 
    // cout_bytes(static_cast<uint8_t>(n1));
    cout_bytes(static_cast<uint8_t>(n2));
    // cout_bytes(static_cast<uint8_t>(n2) & ~static_cast<uint8_t>(p::t_changed));
    cout_bytes(static_cast<uint8_t>(n3));

    std::cout << (static_cast<uint8_t>(n2) & static_cast<uint8_t>(p::t_changed)) << std::endl;
    std::cout << (static_cast<uint8_t>(n3) & static_cast<uint8_t>(p::t_changed)) << std::endl;
    return 0;
}

// 0  has 0
// 2  has 0
// 4  has 0
// 6  has 0
// 8  has 0
// 10 has 0
// 12 has 0
// 14 has 0
// 16 has 0
// 18 has 0
// 20 has 0
// 22 has 0
// 24 has 0
// 26 has 0
// 28 has 0
// 30 has 0