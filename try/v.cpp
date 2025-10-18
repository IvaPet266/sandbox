#include <iostream>
#include <vector>
#include <array>
#include <algorithm>


#include "../include/print/terminal.hpp"

void c(int &e){
        
    e = 903;
    
};
    

int main() {

    std::vector<int> r{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    int x = 0;
    std::string s = "sf";
    bool e = true;

    // c(r[5]);

    for (auto it = r.begin(); it != r.end(); ++it) {
        print(*it);
    };

    // print(r);

    // print(0, s);

    // Исходные массивы
    const size_t SMALL_SIZE = 3;
    using SmallArrayType = std::array<int, SMALL_SIZE>;
    SmallArrayType small_array{{6, 7, 8}};
    
    const size_t BIG_SIZE = 8;
    using BigArrayType = std::array<int, BIG_SIZE>;
    BigArrayType big_array{1, 2, 3, 4, 5};

    // Копируем элементы
    size_t start_position = 5;
    std::copy(small_array.begin(), small_array.end(),
              big_array.begin() + start_position);

    // Проверяем результат
    for(const auto& elem : big_array)
    {
        std::cout << elem << ' ';
    }
    return 0;
}


