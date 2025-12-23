#include <vector>
#include <cmath>
#include <iostream>

struct Point {
    int x, y;
};

std::vector<Point> getIntermediatePoints(Point start, Point end) {
    std::vector<Point> points;
    
    int dx = std::abs(end.x - start.x);
    int dy = std::abs(end.y - start.y);
    
    int sx = (start.x < end.x) ? 1 : -1;
    int sy = (start.y < end.y) ? 1 : -1;
    
    int err = dx - dy;
    int x = start.x;
    int y = start.y;
    
    
    while (true) {
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
        // Проверяем, не достигли ли конечной точки
        if (x == end.x && y == end.y) {
            break;
        }
        points.push_back({x, y});
    }
    
    return points;
}

// Функция для вывода точек (для тестирования)
void printPoints(const std::vector<Point>& points) {
    std::cout << "[";
    for (size_t i = 0; i < points.size(); ++i) {
        std::cout << "(" << points[i].x << ", " << points[i].y << ")";
        if (i != points.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

int main() {
    // Тестирование функции
    std::cout << "Test 1: ";
    auto points1 = getIntermediatePoints({2, 2}, {8, 6});
    printPoints(points1);
    
    std::cout << "Test 2: ";
    auto points2 = getIntermediatePoints({8, 8}, {6, 2});
    printPoints(points2);
    
    std::cout << "Test 3: ";
    auto points3 = getIntermediatePoints({2, 7}, {8, 2});
    printPoints(points3);
    
    std::cout << "Test 4: ";
    auto points4 = getIntermediatePoints({8, 3}, {3, 9});
    printPoints(points4);
    
    return 0;
}