#ifndef EXP_4_CUSTOM_ANGLE_H
#define EXP_4_CUSTOM_ANGLE_H

#include <cmath>

class CustomAngle {

private:
    double degree;

public:
    CustomAngle();

    CustomAngle(double degree_);

    CustomAngle(CustomAngle &custom_angle);

    double get_degree();

    void set_degree(double degree_);

    double GetSin();

    double GetCos();

    double GetTan();
};


#endif //EXP_4_CUSTOM_ANGLE_H
