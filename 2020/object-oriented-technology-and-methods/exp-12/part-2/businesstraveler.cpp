#include "businesstraveler.h"

BusinessTraveler::BusinessTraveler() : Traveler(""), pager("") {
}

BusinessTraveler::BusinessTraveler(const std::string &traveler_str_, const std::string &pager_str_)
        : Traveler(traveler_str_), pager(pager_str_) {
}

/*
 * BusinessTraveler::BusinessTraveler(const BusinessTraveler &business_traveler_) = default;
 */

BusinessTraveler::BusinessTraveler(const BusinessTraveler &business_traveler_)
        : Traveler(business_traveler_), pager(business_traveler_.pager) {
};

/*
 * BusinessTraveler &BusinessTraveler::operator=(const BusinessTraveler &business_traveler_) = default;
 */

BusinessTraveler &BusinessTraveler::operator=(const BusinessTraveler &business_traveler_) {
    Traveler::operator=(business_traveler_);
    this->pager = business_traveler_.pager;
    return *this;
}

void BusinessTraveler::Print() {
    std::cout << "Base Traveler.str: " << this->get_str() << std::endl;
    std::cout << "Pager.str: " << this->pager.get_str() << std::endl;
}
