#include <functional>
#include <iostream>
#include <map>
#include <vector>
#include <array>
#include <algorithm>


#include "../include/print/terminal.hpp"


void c(int &e){
        
    e = 903;
    
};
    

int main() {

    std::vector<int> x = {900, 2112, 212111, 6789};

    auto res = std::find(x.begin(), x.end(), 2112);

    std::cout << (res == x.end()) << std::endl;

    int s = 0;
    s += 5 % 5;
    std::cout << s << std::endl;
    return 0;
}


