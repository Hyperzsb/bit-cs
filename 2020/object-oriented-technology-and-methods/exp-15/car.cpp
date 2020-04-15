#include "car.h"

Car::Car(double distance_, double weight_) : Vehicle(distance_, weight_) {
}

double Car::Fee() {
    return this->distance * 1.2 + this->weight * 1.1;
}
