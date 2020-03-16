#include "csmart.h"

void DoSomething() {
    CSmart csmart;
}

int main() {
    CSmart csmart_1 = CSmart();
    CSmart *csmart_2 = new CSmart();
    DoSomething();
    delete csmart_2;
    return 0;
}