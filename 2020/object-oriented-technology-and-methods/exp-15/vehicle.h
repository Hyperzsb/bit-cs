#ifndef EXP_15_VEHICLE_H
#define EXP_15_VEHICLE_H

class Vehicle {

protected:
    double distance;
    double weight;

public:
    Vehicle(double distance_, double weight_) : distance(distance_), weight(weight_) {};

    virtual double Fee() = 0;

};

#endif //EXP_15_VEHICLE_H
