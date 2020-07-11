#include <cstdio>

int Find(const int *number_list, const int *last_list, int max_length, int number) {
    for (int i = 1; i < max_length; i++)
        if (number_list[last_list[i]] <= number && number_list[last_list[i + 1]] > number)
            return i + 1;
    return 0;
}

int main() {
    int number_num = 0, number_list[200] = {0}, last_list[200] = {0}, max_length = 1;
    scanf("%d", &number_num);
    for (int i = 1; i < number_num; i++) {
        scanf("%d,", &number_list[i]);
        last_list[i] = 0;
    }
    scanf("%d", &number_list[number_num]);
    last_list[number_num] = 0;
    last_list[1] = 1;
    for (int i = 2; i <= number_num; i++)
        if (number_list[last_list[1]] > number_list[i]) {
            last_list[1] = i;
        } else if (number_list[last_list[max_length]] <= number_list[i]) {
            max_length++;
            last_list[max_length] = i;
        } else {
            int tmp = Find(number_list, last_list, max_length, number_list[i]);
            last_list[tmp] = i;
        }
    printf("%d\n", max_length);
    return 0;
}