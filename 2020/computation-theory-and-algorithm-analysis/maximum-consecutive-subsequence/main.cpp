#include <cstdio>

int main() {
    int number_num = 0, number_list[200] = {0},
            tmp_sum = 0, tmp_start = 0, tmp_end = 0, sum = 0, start = 0, end = 0;
    scanf("%d", &number_num);
    for (int i = 0; i < number_num; i++) {
        scanf("%d", &number_list[i]);
        tmp_sum += number_list[i];
        tmp_end = i;
        if (tmp_sum < 0) {
            tmp_sum = 0;
            tmp_start = tmp_end = i + 1;
        } else {
            if (tmp_sum > sum) {
                sum = tmp_sum;
                start = tmp_start;
                end = tmp_end;
            }
        }
    }
    for (int i = start; i < end; i++)
        printf("%d ", number_list[i]);
    printf("%d\n", number_list[end]);
    return 0;
}