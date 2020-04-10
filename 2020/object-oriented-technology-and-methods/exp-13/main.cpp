#include <iostream>
#include <string>
#include "employee.h"
#include "technician.h"
#include "salesman.h"
#include "manager.h"
#include "salesmanager.h"

int main() {
    auto *employee = new Employee(std::string("Employee"), 1000);
    employee->Pay();

    auto *technician = new Technician(std::string("Technician"), 100, 0);
    technician->Pay();

    auto *salesman = new Salesman(std::string("Salesman"), 0.05, 0);
    salesman->Pay();

    auto *manager = new Manager(std::string("Manager"), 7000);
    manager->Pay();

    auto *sales_manager = new SalesManager(std::string("SalesManager"), 0.005, 4000);
    sales_manager->Pay();

    delete employee;
    delete technician;
    delete salesman;
    delete manager;
    delete sales_manager;
    return 0;
}