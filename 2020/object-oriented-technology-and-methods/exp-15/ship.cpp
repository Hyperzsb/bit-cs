#include "ship.h"

Ship::Ship(double distance_, double weight_) : Vehicle(distance_, weight_) {
}

double Ship::Fee() {
    return this->distance * 1.05 + this->weight * 0.9;
}
