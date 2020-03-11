#include "equation.h"

Equation::Equation() {
    this->a = 0;
    this->b = 0;
    this->c = 0;
    this->is_solved = false;
    this->has_root = false;
    this->root_a = 0;
    this->root_b = 0;
}

Equation::Equation(double a_, double b_, double c_) {
    this->a = a_;
    this->b = b_;
    this->c = c_;
    this->is_solved = false;
    this->has_root = false;
    this->root_a = 0;
    this->root_b = 0;
}

double Equation::get_a() {
    return this->a;
}

void Equation::set_a(double a_) {
    this->a = a_;
}

double Equation::get_b() {
    return this->b;
}

void Equation::set_b(double b_) {
    this->b = b_;
}

double Equation::get_c() {
    return this->c;
}

void Equation::set_c(double c_) {
    this->c = c_;
}

bool Equation::HasRoot() {
    if (is_solved) {
        return has_root;
    } else {
        if ((b * b - 4 * a * c) >= 0) {
            this->has_root = true;
            this->is_solved = true;
            this->root_a = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
            this->root_b = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
            return this->has_root;
        } else {
            this->has_root = false;
            this->is_solved = true;
            return this->has_root;
        }
    }
}

double Equation::get_root_a() {
    if (is_solved) {
        return this->root_a;
    } else {
        HasRoot();
        return this->root_a;
    }
}

double Equation::get_root_b() {
    if (is_solved) {
        return this->root_b;
    } else {
        HasRoot();
        return this->root_b;
    }
}
