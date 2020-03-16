#include "array.h"

Array::Array() {
    this->array = new int[10];
    this->is_sorted = false;
    for (int i = 0; i < 10; i++)
        this->array[i] = 0;
}

Array::Array(int array_[], int length) {
    this->array = new int[10];
    this->is_sorted = false;
    int i = 0;
    for (; i < 10 && i < length; i++)
        this->array[i] = array_[i];
    for (; i < 10; i++)
        this->array[i] = 0;
}

Array::~Array() {
    delete[]this->array;
}

void Array::Sort() {
    for (int i = 0; i < 10; i++)
        for (int j = i + 1; j < 10; j++)
            if (array[i] > array[j]) {
                array[i] ^= array[j];
                array[j] ^= array[i];
                array[i] ^= array[j];
            }
    this->is_sorted = true;
}

template<typename T>
void Array::Sort(bool (*compare)(T, T)) {
    for (int i = 0; i < 10; i++)
        for (int j = i + 1; j < 10; j++)
            if (compare(array[i], array[j])) {
                array[i] ^= array[j];
                array[j] ^= array[i];
                array[i] ^= array[j];
            }
    this->is_sorted = true;
}

void Array::Show() {
    if (!this->is_sorted)
        this->Sort();
    for (int i = 0; i < 10; i++)
        std::cout << this->array[i] << " ";
    std::cout << std::endl;
}

template<typename T>
void Array::Show(bool (*compare)(T, T)) {
    if (!this->is_sorted)
        this->Sort(compare);
    if (!compare(array[0], array[1])) {
        for (int i = 0; i < 10; i++)
            std::cout << this->array[i] << " ";
        std::cout << std::endl;
    } else {
        for (int i = 9; i >= 0; i--)
            std::cout << this->array[i] << " ";
        std::cout << std::endl;
    }
}

template
void Array::Sort<int>(bool(*compare)(int, int));

template
void Array::Show<int>(bool(*compare)(int, int));