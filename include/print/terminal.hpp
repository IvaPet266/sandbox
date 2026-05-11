#include "c8_prints.hpp"
#include <vector>


template <typename X>
void print(std::vector<X> entities);

template <typename X, typename Y>
void print(X entity1, Y entity2);

template <typename X, typename Y, typename Z>
void print(X entity1, Y entity2, Z entity3=0);

template <typename T>
void print(T && entity);

void print();