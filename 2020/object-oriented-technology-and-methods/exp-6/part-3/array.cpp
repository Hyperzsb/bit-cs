#include "array.h"

Array::Array() {
    std::cout << "Constructor called." << std::endl;
    this->string = nullptr;
    this->length = 0;
    this->size = 0;
}

Array::Array(int length_) {
    std::cout << "Constructor called." << std::endl;
    this->string = new char[length_];
    this->length = length_;
    this->size = sizeof(this->string);
}

Array::Array(const char *string_) {
    std::cout << "Constructor called." << std::endl;
    this->length = strlen(string_);
    this->string = new char[this->length];
    strcpy(this->string, string_);
    this->size = sizeof(this->string);
}

Array::~Array() {
    if (this->length != 0)
        delete[] this->string;
    std::cout << "Destructor called." << std::endl;
}

char *Array::get_string() {
    return this->string;
}

void Array::set_string(const char *string_) {
    if (this->length != 0) {
        delete this->string;
        this->length = 0;
        this->size = 0;
    }
    this->length = strlen(string_);
    this->string = new char[this->length];
    strcpy(this->string, string_);
    this->size = sizeof(this->string);
}

int Array::get_length() {
    return this->length;
}

int Array::get_size() {
    return this->size;
}

void Array::Copy(Array other_array) {
    if (this->length != 0) {
        delete this->string;
        this->length = 0;
        this->size = 0;
    }
    set_string(other_array.get_string());
}
