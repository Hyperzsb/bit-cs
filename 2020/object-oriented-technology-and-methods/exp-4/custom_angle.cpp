#include "custom_angle.h"

CustomAngle::CustomAngle() {
    this->degree = 0;
}

CustomAngle::CustomAngle(double degree_) : degree(degree_) {
}

CustomAngle::CustomAngle(CustomAngle &custom_angle) {
    this->degree = custom_angle.get_degree();
}

double CustomAngle::get_degree() {
    return this->degree;
}

void CustomAngle::set_degree(double degree_) {
    this->degree = degree_;
}

double CustomAngle::GetSin() {
    return sin(this->degree);
}

double CustomAngle::GetCos() {
    return cos(this->degree);
}

double CustomAngle::GetTan() {
    return tan(this->degree);
}
