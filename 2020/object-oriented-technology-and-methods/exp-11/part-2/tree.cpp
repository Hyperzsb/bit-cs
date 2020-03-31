#include "tree.h"

Tree::Tree(int height_) {
    this->height = height_;
    std::cout << "Tree(): " << this->height << std::endl;
}

Tree::~Tree() {
    std::cout << "~Tree(): " << this->height << std::endl;
}

void Tree::Print() {
    std::cout << "Height: " << this->height << std::endl;
}
