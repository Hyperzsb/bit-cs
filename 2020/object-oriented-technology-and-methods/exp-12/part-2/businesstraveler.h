#ifndef PART_2_BUSINESSTRAVELER_H
#define PART_2_BUSINESSTRAVELER_H

#include <iostream>
#include <string>
#include "traveler.h"
#include "pager.h"

class BusinessTraveler : public Traveler {

private:
    Pager pager;

public:
    BusinessTraveler();

    explicit BusinessTraveler(const std::string &traveler_str_, const std::string &pager_str_);

    BusinessTraveler(const BusinessTraveler &business_traveler_);

    BusinessTraveler &operator=(const BusinessTraveler &business_traveler_);

    void Print();

};


#endif //PART_2_BUSINESSTRAVELER_H
