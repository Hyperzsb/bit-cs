#ifndef EXP_8_CIRCLE_H
#define EXP_8_CIRCLE_H

#include <cmath>

enum Relationship {
    Separation,
    Intersection,
    InternallyTangent,
    ExternallyTangent,
    Inclusion
};

class Circle {

private:
    double x, y;
    double r;

public:
    Circle();

    Circle(double x_, double y_, double r_);

    double get_x();

    void set_x(double x_);

    double get_y();

    void set_y(double y_);

    double get_r();

    void set_r(double r_);

    double DistanceWith(Circle &other_circle);

    Relationship RelationshipWith(Circle &other_circle);

};

double DistanceBetween(Circle &circle_a, Circle &circle_b);

#endif //EXP_8_CIRCLE_H
