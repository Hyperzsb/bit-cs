#ifndef TOPIC_1_COMPLEX_H
#define TOPIC_1_COMPLEX_H

#include <iostream>

class Complex {

private:
    /*
     * 复数的实部
     */
    double real;
    /*
     * 复数的虚部
     */
    double image;

public:
    /*
     * 类的默认构造函数
     */
    Complex();

    /*
     * 类的带有两个双精度浮点数的构造函数，分别定义了复数的实部和虚部
     */
    Complex(double real_,double image_);

    /*
     * 类的拷贝构造函数
     */
    Complex(const Complex &complex_);

    /*
     * 重载+运算符，实现两个复数对象的相加
     */
    Complex &operator+(const Complex &complex_);

    /*
     * 重载+=运算符
     */
    Complex &operator+=(const Complex &complex_);

    /*
     * 重载<<流输出运算符，实现复数对象的流输出
     */
    friend std::ostream &operator<<(std::ostream &ostream_, const Complex &complex_);

};


#endif //TOPIC_1_COMPLEX_H
