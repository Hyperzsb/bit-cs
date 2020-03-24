#include <iostream>
#include "set.h"

int main() {
    int a[] = {1, 3, 5, 7, 6, 4, 2};
    Set S1, S2(a, 7);
    S1 = S2 + 8;
    Set S3 = S1 + S2;
    std::cout << S1 << S2 << S3 << std::endl;

    return 0;
}