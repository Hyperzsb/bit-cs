#include <iostream>
#include "array.h"

int main() {
    std::stringstream input_a("47 34 56 92 103");
    std::stringstream input_b("1 2 3 4 5 6");
    Array<int, 10> array;
    input_b >> (input_a >> array);
    std::cout << "total_length: " << array.get_total_length()
              << " current_length: " << array.get_current_length()
              << std::endl;
    std::cout << array << std::endl;
    array[4] = -1;
    std::cout << array << std::endl;
    return 0;
}