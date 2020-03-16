#include <iostream>

using namespace std;

class ClassOne {
private:
    int i;
public:
    ClassOne();

    ClassOne(int value);

    void Print();

    ~ClassOne();
};

class ClassTwo {
private:
    int i;
    ClassOne my_class;
public:
    ClassTwo();

    ClassTwo(int value);

    void Print();

    ~ClassTwo();
};

ClassOne::ClassOne() : i(0) {
    cout << "This is constructor of ClassOne!" << endl;
}

ClassOne::ClassOne(int value) : i(value) {
    cout << "This is constructor of ClassOne!" << endl;
}

void ClassOne::Print() {
    cout << "The i of ClassOne is " << i << endl;
}

ClassOne::~ClassOne() {
    cout << "This is a destructor!" << endl;
}

ClassTwo::ClassTwo() : i(0) {
    cout << "This is constructor of ClassTwo!" << endl;
}

ClassTwo::ClassTwo(int value) : i(value) {
    cout << "This is constructor of ClassTwo!" << endl;
}

ClassTwo::~ClassTwo() {
    cout << "This is destructor of ClassTwo!" << endl;
}

void ClassTwo::Print() {
    cout << "The i of ClassTwo is " << i << endl;
}
