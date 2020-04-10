#ifndef EXP_13_EMPLOYEE_H
#define EXP_13_EMPLOYEE_H

#include <iostream>
#include <string>

class Employee {

private:
    std::string name;
    int salary;

public:
    Employee();

    Employee(const std::string &name_, int salary_);

    ~Employee();

    std::string get_name();

    int get_salary();

    void Pay();
};

#endif //EXP_13_EMPLOYEE_H
