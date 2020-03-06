#include <iostream>
#include "custom_angle.h"

int main() {
    CustomAngle *custom_angle = new CustomAngle(0.5);
    custom_angle->GetSin();
    custom_angle->GetCos();
    custom_angle->GetTan();
    return 0;
}