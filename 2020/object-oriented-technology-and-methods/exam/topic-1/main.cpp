#include <iostream>
#include "complex.h"

int main() {
    Complex C1(1, 2), C2;
    Complex C3 = C2;
    std::cout << " C3 = " << C3 << std::endl;
    C2 = C1 + C3;
    std::cout << " C2 = " << C2 << std::endl;
    C2 += C1;
    std::cout << " C2 = " << C2 << std::endl;

    return 0;
}
