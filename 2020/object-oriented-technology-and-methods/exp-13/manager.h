#ifndef EXP_13_MANAGER_H
#define EXP_13_MANAGER_H

#include <iostream>
#include <string>
#include "employee.h"

class Manager : virtual public Employee {

public:
    Manager();

    Manager(const std::string &name_, int salary_);

    ~Manager();

    void Pay();

};


#endif //EXP_13_MANAGER_H
