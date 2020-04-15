#ifndef EXP_16_ARRAY_H
#define EXP_16_ARRAY_H

#include <ostream>
#include <sstream>
#include <string>

template<typename T, int _length_>
class Array {

private:
    T array[_length_];
    int total_length;
    int current_length;

public:
    Array();

    int get_total_length();

    int get_current_length();

    friend Array &operator>>(std::stringstream &string_stream, Array<T, _length_> &array_) {
        int index = array_.current_length;
        while (string_stream >> array_.array[index])
            if (++index == array_.total_length)
                break;
        array_.current_length = index;
        return array_;
    };

    friend std::ostream &operator<<(std::ostream &out_stream, const Array<T, _length_> &array_) {
        for (int i = 0; i < array_.current_length; i++)
            out_stream << array_.array[i] << " ";
        return out_stream;
    };

    T &operator[](int index) {
        return this->array[index];
    };
};

template<typename T, int _length_>
Array<T, _length_>::Array() :total_length(_length_), current_length(0) {
    for (int i = 0; i < total_length; i++)
        this->array[i] = 0;
}

template<typename T, int _length_>
int Array<T, _length_>::get_total_length() {
    return _length_;
}

template<typename T, int _length_>
int Array<T, _length_>::get_current_length() {
    return this->current_length;
}

#endif //EXP_16_ARRAY_H
