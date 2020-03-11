#include "pointer.h"

Pointer::Pointer() {
    this->pointer = new int(0);
}

Pointer::Pointer(int number) {
    this->pointer = new int(number);
    std::cout << "Constructor called." << std::endl;
}

Pointer::~Pointer() {
    delete this->pointer;
    std::cout << "Destructor called." << std::endl;
}

const int *Pointer::get_pointer() {
    return this->pointer;
}

void Pointer::Copy(const Pointer &other_pointer) {
    this->pointer = new int(*other_pointer.pointer);
}
