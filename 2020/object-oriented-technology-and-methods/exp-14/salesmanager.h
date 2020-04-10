#ifndef EXP_13_SALESMANAGER_H
#define EXP_13_SALESMANAGER_H

#include <iostream>
#include <string>
#include "manager.h"
#include "salesman.h"

class SalesManager : public Manager, public Salesman {

public:
    SalesManager();

    SalesManager(const std::string &name_, double per_month_rate_, int salary_);

    ~SalesManager();

    void Pay() override;
};


#endif //EXP_13_SALESMANAGER_H
