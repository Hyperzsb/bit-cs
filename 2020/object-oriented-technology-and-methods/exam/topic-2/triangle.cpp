#include "triangle.h"

Triangle::Triangle() : Shape() {
    this->bottom_length = 0;
    this->height = 0;
}

Triangle::Triangle(double bottom_length_, double height_) : Shape() {
    this->bottom_length = bottom_length_;
    this->height = height_;
}

double Triangle::Area() {
    return this->bottom_length * this->height / 2;
}
