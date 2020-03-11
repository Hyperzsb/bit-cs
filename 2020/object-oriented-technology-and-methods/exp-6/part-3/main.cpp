#include <iostream>
#include "array.h"

int main() {
    Array array_a = Array(), array_b = Array("Array");
    std::cout << array_a.get_length() << " " << array_a.get_size() << std::endl;
    std::cout << array_b.get_string() << " " << array_b.get_length() << " " << array_b.get_size() << std::endl;
    array_a.Copy(array_b);
    std::cout << array_a.get_string() << " " << array_a.get_length() << " " << array_a.get_size() << std::endl;
    return 0;
}