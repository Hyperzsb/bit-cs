#include "salesmanager.h"

SalesManager::SalesManager() : Manager(), Salesman(), Employee() {
    std::cout << "SalesManager Default Constructor" << std::endl;
}

SalesManager::SalesManager(const std::string &name_, double per_month_rate_ = 0.005, int salary_ = 4000)
        : Manager(name_, salary_ + 1000), Salesman(name_, per_month_rate_, salary_ + 2000),
          Employee(name_, salary_) {
    std::cout << "SalesManager Constructor Called: name = " + name_ +
                 " per month rate = " << per_month_rate_ <<
              " salary = " << salary_ << std::endl;
}

void SalesManager::Pay() {
    std::cout << "SalesManager:"
                 "\nname = " << this->get_name() <<
              "\nper month rate = " << this->get_per_month_rate() <<
              "\nsalary = " << this->get_salary() << std::endl;
}

SalesManager::~SalesManager() {
    std::cout << "SalesManager Destructor" << std::endl;
}

