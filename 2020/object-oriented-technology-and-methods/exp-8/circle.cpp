#include "circle.h"

Circle::Circle() {
    this->x = 0;
    this->y = 0;
    this->r = 0;
}

Circle::Circle(double x_, double y_, double r_) {
    this->x = x_;
    this->y = y_;
    this->r = r_;
}

double Circle::get_x() {
    return this->x;
}

void Circle::set_x(double x_) {
    this->x = x_;
}

double Circle::get_y() {
    return this->y;
}

void Circle::set_y(double y_) {
    this->y = y_;
}

double Circle::get_r() {
    return this->r;
}

void Circle::set_r(double r_) {
    this->r = r_;
}

double Circle::DistanceWith(Circle &other_circle) {
    return sqrt((this->x - other_circle.get_x()) * (this->x - other_circle.get_x())
                + (this->y - other_circle.get_y()) * (this->y - other_circle.get_y()));
}

Relationship Circle::RelationshipWith(Circle &other_circle) {
    if (this->DistanceWith(other_circle) > this->r + other_circle.get_r())
        return Separation;
    else if (this->DistanceWith(other_circle) == this->r + other_circle.get_r())
        return ExternallyTangent;
    else if (this->DistanceWith(other_circle) < this->r + other_circle.get_r()
             && this->DistanceWith(other_circle) > std::abs(this->r - other_circle.get_r()))
        return Intersection;
    else if (this->DistanceWith(other_circle) == std::abs(this->r - other_circle.get_r()))
        return InternallyTangent;
    else
        return Inclusion;
}

double DistanceBetween(Circle &circle_a, Circle &circle_b) {
    return sqrt((circle_a.get_x() - circle_b.get_x()) * (circle_a.get_x() - circle_b.get_x())
                + (circle_a.get_y() - circle_b.get_y()) * (circle_a.get_y() - circle_b.get_y()));
}
