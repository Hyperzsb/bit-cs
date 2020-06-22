#ifndef TOPIC_2_CIRCLE_H
#define TOPIC_2_CIRCLE_H

#include "shape.h"

class Circle : virtual public Shape {

private:
    /*
     * 圆的半径
     */
    double radius;

public:
    /*
     * Circle类的默认构造函数
     */
    Circle();

    /*
     * Circle类的构造函数，初始化了圆的半径
     */
    explicit Circle(double radius_);

    /*
     * Override的Area()函数，用于求圆的面积
     */
    double Area() override;

};


#endif //TOPIC_2_CIRCLE_H
