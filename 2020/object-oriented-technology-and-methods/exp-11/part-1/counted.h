#ifndef PART_1_COUNTED_H
#define PART_1_COUNTED_H

#include <iostream>

class Counted {

private:
    static int count;
    int id;

public:
    Counted();

    ~Counted();

};

#endif //PART_1_COUNTED_H
