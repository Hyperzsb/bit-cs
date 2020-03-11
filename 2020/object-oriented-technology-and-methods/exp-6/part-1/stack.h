#ifndef PART_1_STACK_H
#define PART_1_STACK_H

#include <iostream>
#include <cstdlib>

template<typename T>
class Stack {

private:
    struct Element {
        T data;
        Element *next;

        Element() {
            data = T();
            next = NULL;
        }

        Element(const T &_data, Element *_next) {
            data = _data;
            next = _next;
        }
    };

    int size_;
    Element *top_;
    Element *base_;

public:
    Stack();

    ~Stack();

    void Push(const T &data);

    T Top();

    T Pop();

    int size();

    bool Empty();
};


#endif //PART_1_STACK_H
