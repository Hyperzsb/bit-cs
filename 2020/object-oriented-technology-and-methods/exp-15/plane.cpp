#include "plane.h"

Plane::Plane(double distance_, double weight_) : Vehicle(distance_, weight_) {
}

double Plane::Fee() {
    return this->distance * 1.15 + this->weight * 1.05;
}
