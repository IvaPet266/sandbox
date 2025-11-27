#include "c8_prints.hpp"
#include <vector>


template <typename X>
void print(std::vector<X> entities) {
    for (int i=0; i < entities.size(); i++) {
        std::cout << entities[i] << " ";
    };
    std::cout<<std::endl;
};

template <typename X, typename Y>
void print(X entity1, Y entity2) {
    std::cout << entity1 << " || " << entity2 << std::endl;
};

template <typename X, typename Y, typename Z>
void print(X entity1, Y entity2, Z entity3=0) {
    std::cout << entity1 << " || " << entity2;
    if (entity3) {
        std::cout << " || " << entity3;
    };
    std::cout << std::endl;
};

template <typename T>
void print(T && entity) {
    std::cout << entity << std::endl;
};

void print() {
    std::cout << std::endl;
}