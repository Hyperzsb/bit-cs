#include "counted.h"

Counted::Counted() {
    this->id = count++;
    std::cout << "Constructor called at id = " << this->id << std::endl;
}

Counted::~Counted() {
    std::cout << "Destructor called at id = " << this->id << std::endl;
}

int Counted::count = 0;