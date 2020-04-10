#include "employee.h"

Employee::Employee() {
    std::cout << "Employee Default Constructor" << std::endl;
    this->name.assign("");
    this->salary = 0;
}

Employee::Employee(const std::string &name_, int salary_) {
    std::cout << "Employee Constructor Called: name = " + name_ +
                 " salary = " << salary_ << std::endl;
    this->name.assign(name_);
    this->salary = salary_;
}

std::string Employee::get_name() {
    return this->name;
}

int Employee::get_salary() {
    return this->salary;
}

Employee::~Employee() {
    std::cout << "Employee Destructor" << std::endl;
}

void Employee::Pay() {
    std::cout << "Employee:"
                 "\nname = " << this->get_name() <<
              "\nsalary = " << this->get_salary() << std::endl;
}
