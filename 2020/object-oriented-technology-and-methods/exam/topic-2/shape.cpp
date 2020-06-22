#include "shape.h"

Shape::Shape() = default;

double Shape::Area() {
    return 0;
}

double PrintArea(Shape &shape) {
    return shape.Area();
}
