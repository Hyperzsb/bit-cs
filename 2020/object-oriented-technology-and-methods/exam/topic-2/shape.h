#ifndef TOPIC_2_SHAPE_H
#define TOPIC_2_SHAPE_H


class Shape {

public:
    /*
     * Shape类的默认构造函数
     */
    Shape();

    /*
     * 虚函数，用于求形状的面积
     */
    virtual double Area();

    /*
     * 友元函数，用于输出形状的面积
     */
    friend double PrintArea(Shape &shape);
};



#endif //TOPIC_2_SHAPE_H
