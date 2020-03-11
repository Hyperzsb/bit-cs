#include "stack.h"

template<typename T>
Stack<T>::Stack() : size_(0) {
    std::cout << "Constructor called." << std::endl;
    top_ = new Element();
    base_ = top_;
}

template<typename T>
Stack<T>::~Stack() {
    std::cout << "Destructor called." << std::endl;
    while (!Empty())
        Pop();
}

template<typename T>
void Stack<T>::Push(const T &data) {
    if (size_ == 0) {
        top_->next = new Element(data, NULL);
        base_ = top_->next;
        size_ = 1;
        return;
    } else {
        top_->next = new Element(data, top_->next);
        size_++;
        return;
    }
}

template<typename T>
T Stack<T>::Top() {
    if (size_ == 0) {
        return top_->data;
    } else {
        return top_->next->data;
    }
}

template<typename T>
T Stack<T>::Pop() {
    if (size_ == 0) {
        return top_->data;
    } else {
        Element *top_element = top_->next;
        T top_data = top_element->data;
        top_->next = top_element->next;
        delete top_element;
        return top_data;
    }
}

template<typename T>
int Stack<T>::size() {
    return size_;
}

template<typename T>
bool Stack<T>::Empty() {
    if (size_ == 0) {
        return true;
    } else {
        return false;
    }
}

template
class Stack<int>;