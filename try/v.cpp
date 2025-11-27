#include <functional>
#include <iostream>
#include <ctime>
#include <map>
#include <vector>
#include <array>
#include <algorithm>


#include "../include/print/terminal.hpp"


int c(){
        
    return std::rand() % 3;
    
};
    

int main() {
    std::srand(std::time(0));

    int count = std::rand() % 500;
    while (count != 0) {
        std::cout << count << std::endl;
        count = std::rand() % 500;
    };
    return 0;
}


