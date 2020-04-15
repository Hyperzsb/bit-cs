#include <iostream>
#include "vehicle.h"
#include "plane.h"
#include "ship.h"
#include "car.h"

int main() {
    Vehicle *plane = new Plane(1000, 500);
    Vehicle *ship = new Ship(1000, 500);
    Vehicle *car = new Car(1000, 500);
    std::cout << "Plane fee: " << plane->Fee()
              << "\nShip fee: " << ship->Fee()
              << "\nCar fee: " << car->Fee()
              << std::endl;
    return 0;
}