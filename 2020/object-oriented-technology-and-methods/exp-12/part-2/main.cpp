#include "businesstraveler.h"

int main() {
    BusinessTraveler business_traveler_a("Joe BusinessMan", "Pager 1");
    business_traveler_a.Print();
    BusinessTraveler business_traveler_b("Jane BusinessWoman", "Pager 2");
    business_traveler_b.Print();
    /**
     * TODO
     * What is the difference between:
     * *business_traveler_b = *business_traveler_a;
     * and
     * business_traveler_b = business_traveler_a;
     * ?
     * And if we use:
     * business_traveler_b = business_traveler_a;
     * Does the original instance or its memory for business_traveler_b still exist?
     */
    BusinessTraveler business_traveler_c;
    business_traveler_c.Print();
    BusinessTraveler business_traveler_d(business_traveler_a);
    business_traveler_d.Print();
    business_traveler_c = business_traveler_b;
    business_traveler_c.Print();

    return 0;
}