#include "set.h"

Set::Set() {
    this->set = nullptr;
    this->size = 0;
}

Set::Set(const int *set_, int size_) {
    this->set = new int[size_];
    for (int i = 0; i < size_; i++)
        this->set[i] = set_[i];
    this->size = size_;
}

Set::Set(const Set &set_) {
    if (set_.size != 0) {
        this->set = new int[set_.size];
        for (int i = 0; i < set_.size; i++)
            this->set[i] = set_.set[i];
        this->size = set_.size;
    } else {
        this->set = nullptr;
        this->size = 0;
    }
}

int Set::get_size() {
    return this->size;
}

Set::~Set() {
    delete[]this->set;
}

bool Set::IsExist(int num) {
    for (int i = 0; i < this->size; i++)
        if (this->set[i] == num)
            return true;
    return false;
}

Set &Set::operator=(const Set &set_) {
    delete[]this->set;
    this->set = new int[set_.size];
    for (int i = 0; i < set_.size; i++)
        this->set[i] = set_.set[i];
    this->size = set_.size;
    return *this;
}

Set &Set::operator+(int num) {
    int *tmp_set = new int[this->size + 1], tmp_size = this->size + 1;
    for (int i = 0; i < this->size; i++)
        tmp_set[i] = this->set[i];
    tmp_set[this->size] = num;
    delete[]this->set;
    this->set = new int[tmp_size];
    for (int i = 0; i < tmp_size; i++)
        this->set[i] = tmp_set[i];
    this->size = tmp_size;
    delete[]tmp_set;
    return *this;
}

Set &Set::operator+=(int num) {
    return *this + num;
}

Set operator+(const Set &set_a, const Set &set_b) {
    Set tmp_set = set_a;
    return tmp_set += set_b;
}

Set &Set::operator+=(const Set &set_) {
    int *tmp_set = new int[this->size + set_.size], tmp_size = 0;
    for (int i = 0; i < this->size; i++)
        for (int j = 0; j < set_.size; j++)
            if (this->set[i] == set_.set[j])
                tmp_set[tmp_size++] = this->set[i];
    delete[]this->set;
    if (tmp_size != 0) {
        this->set = new int[tmp_size];
        for (int i = 0; i < tmp_size; i++)
            this->set[i] = tmp_set[i];
        this->size = tmp_size;
        delete[]tmp_set;
    } else {
        this->set = nullptr;
        this->size = 0;
    }
    return *this;
}

std::ostream &operator<<(std::ostream &ostream_, const Set &set_) {
    if (set_.size != 0) {
        for (int i = 0; i < set_.size; i++)
            ostream_ << set_.set[i] << " ";
        ostream_ << std::endl;
    } else {
        ostream_ << "empty" << std::endl;
    }
    return ostream_;
}

