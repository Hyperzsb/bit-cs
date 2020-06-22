#ifndef TOPIC_3_MYARRAY_H
#define TOPIC_3_MYARRAY_H

#include <iostream>

template<typename T>
class MyArray {

private:
    /*
     * 数组的长度
     */
    int length;
    /*
     * 数组的存储位置
     */
    T *array;

public:
    /*
     * MyArray类的默认构造函数
     */
    MyArray() : length(0), array(NULL) {};

    /*
     * MyArray类的构造函数，定义了数组的长度，初始化了数组空间
     */
    explicit MyArray(int length_) : length(length_), array(new T[length_]) {};

    /*
     * 重载了[]运算符
     */
    T &operator[](int index) {
        return this->array[index];
    };

    /*
     * 友元函数，重载了<<运算符
     */
    friend std::ostream &operator<<(std::ostream &ostream_, const MyArray<T> &my_array_) {
        for (int i = 0; i < my_array_.length; i++)
            ostream_ << my_array_.array[i] << " ";
        return ostream_;
    };

};


#endif //TOPIC_3_MYARRAY_H
