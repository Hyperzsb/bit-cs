#include <iostream>
#include "shape.h"
#include "circle.h"
#include "triangle.h"

int main() {
    Shape *p = new Circle(2);
    std::cout << "The area of the circle is: " << PrintArea(*p) << std::endl;
    Triangle triangle(3, 4);
    std::cout << "The area of the triangle is: " << PrintArea(triangle) << std::endl;
    delete p;

    return 0;
}
