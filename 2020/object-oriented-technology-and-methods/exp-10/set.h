#ifndef EXP_10_SET_H
#define EXP_10_SET_H

#include <iostream>

class Set {

private:
    int *set;
    int size;

public:
    Set();

    Set(const int *set_, int size_);

    Set(const Set &set_);

    ~Set();

    int get_size();

    bool IsExist(int num);

    Set &operator=(const Set &set_);

    Set &operator+(int num);

    Set &operator+=(int num);

    friend Set operator+(const Set &set_a, const Set &set_b);

    Set &operator+=(const Set &set_);

    friend std::ostream &operator<<(std::ostream &ostream_, const Set &set_);
};

#endif //EXP_10_SET_H
