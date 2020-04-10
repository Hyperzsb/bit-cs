#include "salesman.h"

Salesman::Salesman() : Employee() {
    std::cout << "Salesman Default Constructor" << std::endl;
    this->per_month_rate = 0;
}

Salesman::Salesman(const std::string &name_, double per_month_rate_ = 0.05, int salary_ = 0)
        : Employee(name_, salary_) {
    std::cout << "Salesman Constructor Called: name = " + name_ +
                 " per month rate = " << per_month_rate_ <<
              " salary = " << salary_ << std::endl;
    this->per_month_rate = per_month_rate_;
}

double Salesman::get_per_month_rate() {
    return this->per_month_rate;
}

void Salesman::Pay() {
    std::cout << "Salesman:"
                 "\nname = " << this->get_name() <<
              "\nper month rate = " << this->get_per_month_rate() <<
              "\nsalary = " << this->get_salary() << std::endl;
}

Salesman::~Salesman() {
    std::cout << "Salesman Destructor" << std::endl;
}
