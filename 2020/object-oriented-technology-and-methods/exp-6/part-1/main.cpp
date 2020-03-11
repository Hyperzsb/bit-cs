#include <iostream>
#include "stack.h"

int main() {
    Stack<int> stack;
    for (int i = 0; i < 10; i++)
        stack.Push(i);
    while (!stack.Empty()) {
        int tmp = stack.Pop();
        std::cout << tmp << std::endl;
    }
    return 0;
}