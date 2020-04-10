#ifndef EXP_13_TECHNICIAN_H
#define EXP_13_TECHNICIAN_H

#include <iostream>
#include <string>
#include "employee.h"

class Technician : virtual public Employee {

private:
    int per_hour_salary;

public:
    Technician();

    Technician(const std::string &name_, int per_hour_salary_, int salary_);

    ~Technician();

    int get_per_hour_salary();

    void Pay();
};


#endif //EXP_13_TECHNICIAN_H
