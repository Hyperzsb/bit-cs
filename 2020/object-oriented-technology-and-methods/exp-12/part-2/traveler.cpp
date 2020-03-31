#include "traveler.h"

Traveler::Traveler(const std::string &str_) {
    this->str.assign(str_);
}

Traveler::Traveler(const Traveler &traveler_) {
    this->str.assign(traveler_.str);
}

Traveler &Traveler::operator=(const Traveler &traveler_) {
    this->str.assign(traveler_.str);
    return *this;
}

std::string Traveler::get_str() {
    return this->str;
}

void Traveler::set_str(const std::string &str_) {
    this->str.assign(str_);
}
