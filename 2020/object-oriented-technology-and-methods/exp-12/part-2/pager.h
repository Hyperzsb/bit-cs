#ifndef PART_2_PAGER_H
#define PART_2_PAGER_H

#include <string>

class Pager {

private:
    std::string str;

public:
    explicit Pager(const std::string &str_);

    Pager(const Pager &pager_);

    Pager &operator=(const Pager &pager_);

    std::string get_str();

};

#endif //PART_2_PAGER_H
