#ifndef EXP_15_CAR_H
#define EXP_15_CAR_H

#include "vehicle.h"

class Car : public Vehicle {

public:
    Car(double distance_, double weight_);

    double Fee() override;
};


#endif //EXP_15_CAR_H
