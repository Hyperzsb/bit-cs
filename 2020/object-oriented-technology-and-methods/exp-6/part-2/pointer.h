#ifndef PART_2_POINTER_H
#define PART_2_POINTER_H

#include <iostream>

class Pointer {

private:
    int *pointer;

public:
    Pointer();

    Pointer(int number);

    ~Pointer();

    const int *get_pointer();

    void Copy(const Pointer &pointer);

};


#endif //PART_2_POINTER_H
