#include "complex.h"

Complex::Complex() {
    this->real = 0;
    this->image = 0;
}

Complex::Complex(double real_, double image_) {
    this->real = real_;
    this->image = image_;
}

Complex::Complex(const Complex &complex_) {
    this->real = complex_.real;
    this->image = complex_.image;
}

Complex &Complex::operator+(const Complex &complex_) {
    this->real += complex_.real;
    this->image += complex_.image;
    return *this;
}

Complex &Complex::operator+=(const Complex &complex_) {
    return *this + complex_;
}

std::ostream &operator<<(std::ostream &ostream_, const Complex &complex_) {
    if (complex_.real != 0) {
        if (complex_.image > 0)
            ostream_ << complex_.real << "+" << complex_.image << "i";
        else if (complex_.image < 0)
            ostream_ << complex_.real << complex_.image << "i";
        else
            ostream_ << complex_.real;
    } else {
        if (complex_.image != 0)
            ostream_ << complex_.image << "i";
        else
            ostream_ << "0";
    }
    return ostream_;
}
