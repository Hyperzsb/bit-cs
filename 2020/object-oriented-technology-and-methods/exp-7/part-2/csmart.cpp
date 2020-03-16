#include "csmart.h"

CSmart::CSmart() {
    total++;
    std::cout << "Total: " << total << std::endl;
}

CSmart::~CSmart() {
    total--;
    std::cout << "Total: " << total << std::endl;
}

int CSmart::total = 0;
