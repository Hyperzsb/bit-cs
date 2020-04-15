#ifndef EXP_15_PLANE_H
#define EXP_15_PLANE_H

#include "vehicle.h"

class Plane : public Vehicle {

public:
    Plane(double distance_, double weight_);

    double Fee() override;

};


#endif //EXP_15_PLANE_H
