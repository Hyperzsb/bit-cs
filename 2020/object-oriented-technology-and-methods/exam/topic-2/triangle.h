#ifndef TOPIC_2_TRIANGLE_H
#define TOPIC_2_TRIANGLE_H

#include "shape.h"

class Triangle : virtual public Shape {

private:
    /*
     * 三角形的底
     */
    double bottom_length;
    /*
     * 三角形的高
     */
    double height;

public:
    /*
     * Triangle类的默认构造函数
     */
    Triangle();

    /*
     * Triangle类的构造函数，定义了三角形的底和高
     */
    Triangle(double bottom_length_,double height_);

    /*
     * Override的Area()函数，用于求三角形的面积
     */
    double Area() override;

};


#endif //TOPIC_2_TRIANGLE_H
