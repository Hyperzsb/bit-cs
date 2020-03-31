#include <iostream>
#include "tree.h"

Tree tree_a = Tree(10);

int main() {

    Tree tree_b = Tree(20);
    static Tree tree_c = Tree(30);
    Tree *tree_d = new Tree(40);

    tree_a.Print();
    std::cout << "&tree_a: " << &tree_a << std::endl;
    tree_b.Print();
    std::cout << "&tree_b: " << &tree_b << std::endl;
    tree_c.Print();
    std::cout << "&tree_c: " << &tree_c << std::endl;
    tree_d->Print();
    std::cout << "&tree_d: " << &tree_d << std::endl;
    std::cout << "&(*tree_d): " << &(*tree_d) << std::endl;

    delete tree_d;

    return 0;
}