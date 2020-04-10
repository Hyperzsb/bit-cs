#include <iostream>
#include <string>
#include "employee.h"
#include "technician.h"
#include "salesman.h"
#include "manager.h"
#include "salesmanager.h"

int main() {
    Employee *employee = new Employee(std::string("Employee"), 1000);
    employee->Pay();

    Employee *technician = new Technician(std::string("Technician"), 100, 0);
    technician->Pay();

    Employee *salesman = new Salesman(std::string("Salesman"), 0.05, 0);
    salesman->Pay();

    Employee *manager = new Manager(std::string("Manager"), 7000);
    manager->Pay();

    Employee *sales_manager = new SalesManager(std::string("SalesManager"), 0.005, 4000);
    sales_manager->Pay();

    delete employee;
    delete technician;
    delete salesman;
    delete manager;
    delete sales_manager;
    return 0;
}