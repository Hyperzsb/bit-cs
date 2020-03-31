#include "pager.h"

Pager::Pager(const std::string &str_) {
    this->str.assign(str_);
}

Pager::Pager(const Pager &pager_) {
    this->str.assign(pager_.str);
}

Pager &Pager::operator=(const Pager &pager_) {
    this->str.assign(pager_.str);
    return *this;
}

std::string Pager::get_str() {
    return this->str;
}
