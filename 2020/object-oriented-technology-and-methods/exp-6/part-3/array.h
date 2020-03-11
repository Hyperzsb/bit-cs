#ifndef PART_3_ARRAY_H
#define PART_3_ARRAY_H

#include <iostream>
#include <cstring>

class Array {

private:
    char *string;
    int length;
    int size;

public:
    Array();

    Array(int length_);

    Array(const char *string_);

    ~Array();

    char *get_string();

    void set_string(const char *string_);

    int get_length();

    int get_size();

    void Copy(Array other_array);
};


#endif //PART_3_ARRAY_H
