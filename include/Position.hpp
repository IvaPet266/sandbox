// #include <iostream>
#include <string>

#pragma once


struct Position {

  int x = 0;
  int y = 0;
  
  std::string to_string() {
    return "x -> " + std::to_string(x) + " y -> " + std::to_string(y);
  }
};
