#ifndef PART_2_TREE_H
#define PART_2_TREE_H

#include <iostream>

class Tree {

private:
    int height;

public:
    explicit Tree(int height_ = 0);

    ~Tree();

    void Print();
};

#endif //PART_2_TREE_H
