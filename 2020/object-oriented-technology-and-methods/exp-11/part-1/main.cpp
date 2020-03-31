#include "counted.h"

int main() {
    Counted counted_a = Counted();
    Counted *counted_b = new Counted();
    Counted *counted_list = new Counted[3];
    delete counted_b;
    delete[]counted_list;
    return 0;
}