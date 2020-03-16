#include <iostream>
#include "keepstring.h"

int main() {
    KeepString keep_string = KeepString("Internal String");
    const char *string = keep_string.get_string();
    std::cout << string << std::endl;
    return 0;
}