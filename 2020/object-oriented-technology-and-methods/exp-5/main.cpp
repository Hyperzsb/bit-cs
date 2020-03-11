#include <iostream>
#include "equation.h"

int main() {
    Equation equation_a = Equation();
    equation_a.set_a(1);
    equation_a.set_b(2);
    equation_a.set_c(2);
    Equation equation_b = Equation(1, 2, 1);
    if (equation_a.HasRoot()) {
        std::cout << "Root a is: " << equation_a.get_root_a() << std::endl;
        std::cout << "Root b is: " << equation_a.get_root_b() << std::endl;
    } else {
        std::cout << "No root for this equation." << std::endl;
    }
    if (equation_b.HasRoot()) {
        std::cout << "Root a is: " << equation_b.get_root_a() << std::endl;
        std::cout << "Root b is: " << equation_b.get_root_b() << std::endl;
    } else {
        std::cout << "No root for this equation." << std::endl;
    }
    return 0;
}
