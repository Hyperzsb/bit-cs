#ifndef PART_1_ARRAY_H
#define PART_1_ARRAY_H

#include <iostream>

class Array {

private:
    int *array;
    bool is_sorted;

public:
    Array();

    Array(int array_[], int length);

    ~Array();

    void Sort();

    template<typename T>
    void Sort(bool (*compare)(T, T));

    void Show();

    template<typename T>
    void Show(bool (*compare)(T, T));

};

#endif //PART_1_ARRAY_H
