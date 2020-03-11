#ifndef EXP_5_EQUATION_H
#define EXP_5_EQUATION_H

#include <cmath>

class Equation {

private:
    double a;
    double b;
    double c;
    bool is_solved;
    bool has_root;
    double root_a;
    double root_b;

public:
    Equation();

    Equation(double a_, double b_, double c_);

    double get_a();

    void set_a(double a_);

    double get_b();

    void set_b(double b_);

    double get_c();

    void set_c(double c_);

    bool HasRoot();

    double get_root_a();

    double get_root_b();

};


#endif //EXP_5_EQUATION_H
