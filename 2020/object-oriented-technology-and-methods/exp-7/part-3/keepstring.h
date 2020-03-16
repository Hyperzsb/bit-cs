#ifndef PART_3_KEEPSTRING_H
#define PART_3_KEEPSTRING_H

#include <cstring>

class KeepString {

private:
    char *string;

public:
    KeepString();

    KeepString(const char *string_);

    char *get_string();

};

#endif //PART_3_KEEPSTRING_H
