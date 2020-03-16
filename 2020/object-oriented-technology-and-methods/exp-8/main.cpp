#include <iostream>
#include "circle.h"

int main() {
    Circle circle_a = Circle(0, 0, 1);
    Circle circle_b = Circle(2, 0, 1);
    std::cout << circle_a.DistanceWith(circle_b) << std::endl;
    std::cout << circle_b.DistanceWith(circle_a) << std::endl;
    std::cout << DistanceBetween(circle_a, circle_b) << std::endl;
    std::cout << circle_a.RelationshipWith(circle_b) << std::endl;
    std::cout << circle_b.RelationshipWith(circle_a) << std::endl;
    Circle circle_c = Circle(0, 1, 1);
    Circle circle_d = Circle(0, 3, 1);
    std::cout << circle_a.RelationshipWith(circle_c) << std::endl;
    std::cout << circle_a.RelationshipWith(circle_d) << std::endl;

    return 0;
}