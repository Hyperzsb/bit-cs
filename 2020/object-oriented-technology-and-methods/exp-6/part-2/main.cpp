#include <iostream>
#include "pointer.h"

int main() {
    Pointer pointer_a = Pointer(10), pointer_b = Pointer(20);
    std::cout << *pointer_a.get_pointer() << std::endl;
    std::cout << *pointer_b.get_pointer() << std::endl;
    pointer_b.Copy(pointer_a);
    std::cout << *pointer_b.get_pointer() << std::endl;
    return 0;
}