#include "circle.h"

Circle::Circle() : Shape() {
    this->radius = 0;
}

Circle::Circle(double radius_) : Shape() {
    this->radius = radius_;
}

double Circle::Area() {
    return 3.1415926 * this->radius * this->radius;
}
