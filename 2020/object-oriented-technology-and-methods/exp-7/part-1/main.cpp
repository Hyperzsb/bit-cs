#include "array.h"

bool CompareA(int a, int b) {
    return a > b;
}

bool CompareB(int a, int b) {
    return a < b;
}

int main() {
    int arr[9] = {1, 7, 3, 5, 11, 9, 6, 15, 10};
    Array array = Array(arr, sizeof(arr) / sizeof(arr[0]));
    array.Sort(CompareA);
    array.Show();
    array.Show(CompareA);
    array.Show(CompareB);
    array.Sort(CompareB);
    array.Show();
    array.Show(CompareB);
    array.Show(CompareA);
    return 0;
}