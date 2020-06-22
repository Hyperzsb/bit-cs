#include <iostream>
#include "myarray.h"

int main() {
    MyArray<int> intArray(10);     // 10 is the number of elements in intArray
    for (int i = 0; i < 10; i++)
        intArray[i] = i * i;
    std::cout << intArray << std::endl;

    return 0;
}
