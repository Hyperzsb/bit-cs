#include<stdio.h>
#include<math.h>

bool ck(double middle_index, int cable_num, int final_num, const double *cable_list) {
    int sum = 0;
    for (int i = 0; i < cable_num; i++)
        sum += (int) (cable_list[i] / middle_index);
    return sum >= final_num;
}

int main() {
    double cable_list[100005];
    int cable_num, final_num;
    scanf("%d%d", &cable_num, &final_num);
    for (int i = 0; i < cable_num; i++)
        scanf("%lf", &cable_list[i]);
    double left_index = 0, right_index = 100005, middle_index = 0;
    int i = 1000;
    for (int i = 0; i < 1000; i++) {
        middle_index = (left_index + right_index) / 2;
        if (ck(middle_index, cable_num, final_num, cable_list))
            left_index = middle_index;
        else
            right_index = middle_index;
    }
    printf("%0.2lf\n", (floor(right_index * 100)) / 100);
    return 0;
}