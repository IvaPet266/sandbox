#include <string>
#include <iostream>
#include <vector>

#pragma once


struct Position {

  int x = 0;
  int y = 0;
  
  std::string to_string() {
    return "x -> " + std::to_string(x) + " y -> " + std::to_string(y);
  }

  static Position interpolate(Position& p1, Position& p2) {
    if (p1.x == p2.x && p1.y == p2.y) return p1;
    
    int dx = std::abs(p2.x - p1.x);
    int dy = std::abs(p2.y - p1.y);
    
    int sx = (p1.x < p2.x) ? 1 : -1;
    int sy = (p1.y < p2.y) ? 1 : -1;
    
    int err = dx - dy;
    int x = p1.x;
    int y = p1.y;
  
      int e2 = 2 * err;
      if (e2 > -dy) {
          err -= dy;
          x += sx;
      }
      if (e2 < dx) {
          err += dx;
          y += sy;
      }
      return Position{x, y};
}
};
