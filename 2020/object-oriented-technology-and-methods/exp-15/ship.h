#ifndef EXP_15_SHIP_H
#define EXP_15_SHIP_H

#include "vehicle.h"

class Ship : public Vehicle {

public:
    Ship(double distance_, double weight_);

    double Fee() override;
};


#endif //EXP_15_SHIP_H
