#include <iostream>

using namespace std;

class B1 {

private:
    int b;

public:
    explicit B1(int i) : b(i) {
        cout << "Constructor B1:" << b << endl;
    }

    ~B1() {
        cout << "Des B1:" << b << endl;
    }
};

class B2 {

private:
    int b;

public:
    explicit B2(int i) : b(i) {
        cout << "Constructor B2:" << b << endl;
    }

    ~B2() {
        cout << "Des B2:" << b << endl;
    }
};

class Y : public B1, public B2 {

private:
    const B2 x4;
    B1 x1, x2;
    B1 &x3;
    static B2 x5;

public:
    Y(int i, int j, int m, int n, int o) : x2(i), x1(j), B2(m), B1(n), x3(x2), x4(o) {
        cout << "Constructor Y:" << endl;
    }

    ~Y() {
        cout << "Des Y:" << endl;
    }
};

B2 Y::x5 = B2(-1);

int main() {
    Y y = Y(1, 2, 3, 4, 5);
    return 0;
}