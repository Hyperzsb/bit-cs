#ifndef EXP_13_SALESMAN_H
#define EXP_13_SALESMAN_H

#include <iostream>
#include <string>
#include "employee.h"

class Salesman : virtual public Employee {

private:
    double per_month_rate;

public:
    Salesman();

    Salesman(const std::string &name_, double per_month_rate, int salary_);

    ~Salesman();

    double get_per_month_rate();

    void Pay() override;
};

#endif //EXP_13_SALESMAN_H
