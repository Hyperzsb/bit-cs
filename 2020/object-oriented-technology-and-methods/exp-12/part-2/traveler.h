#ifndef PART_2_TRAVELER_H
#define PART_2_TRAVELER_H

#include <string>

class Traveler {

private:
    std::string str;

public:
    explicit Traveler(const std::string &str_);

    Traveler(const Traveler &traveler_);

    Traveler &operator=(const Traveler &traveler_);

    std::string get_str();

    void set_str(const std::string &str_);

};

#endif //PART_2_TRAVELER_H
