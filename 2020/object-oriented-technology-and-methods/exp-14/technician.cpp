#include "technician.h"

Technician::Technician() : Employee() {
    std::cout << "Technician Default Constructor" << std::endl;
    this->per_hour_salary = 0;
}

Technician::Technician(const std::string &name_, int per_hour_salary_ = 100, int salary_ = 0)
        : Employee(name_, salary_) {
    std::cout << "Technician Constructor Called: name = " + name_ +
                 " per hour salary = " << per_hour_salary_ <<
              " salary = " << salary_ << std::endl;
    this->per_hour_salary = per_hour_salary_;
}

int Technician::get_per_hour_salary() {
    return this->per_hour_salary;
}

void Technician::Pay() {
    std::cout << "Technician:"
                 "\nname = " << this->get_name() <<
              "\nper hour salary = " << this->get_per_hour_salary() <<
              "\nsalary = " << this->get_salary() << std::endl;
}

Technician::~Technician() {
    std::cout << "Technician Destructor" << std::endl;
}
