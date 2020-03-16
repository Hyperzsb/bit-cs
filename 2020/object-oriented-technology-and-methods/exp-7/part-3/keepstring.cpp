#include "keepstring.h"

KeepString::KeepString() {
    this->string = nullptr;
}

KeepString::KeepString(const char *string_) {
    int length = strlen(string_);
    this->string = new char[length + 1];
    for (int i = 0; i < length; i++)
        this->string[i] = string_[i];
    this->string[length] = '\0';
}

char *KeepString::get_string() {
    return this->string;
}
