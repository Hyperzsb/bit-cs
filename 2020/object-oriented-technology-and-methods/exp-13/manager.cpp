#include "manager.h"

Manager::Manager() : Employee() {
    std::cout << "Manager Default Constructor" << std::endl;
}

Manager::Manager(const std::string &name_, int salary_ = 7000) : Employee(name_, salary_) {
    std::cout << "Manager Constructor Called: name = " + name_ +
                 " salary = " << salary_ << std::endl;
}

void Manager::Pay() {
    std::cout << "Manager:"
                 "\nname = " << this->get_name() <<
              "\nsalary = " << this->get_salary() << std::endl;
}

Manager::~Manager() {
    std::cout << "Manager Destructor" << std::endl;
}
