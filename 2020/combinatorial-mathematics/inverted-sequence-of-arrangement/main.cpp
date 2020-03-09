#include <cstdio>

long long map[12] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800};

void Swap(long long &a, long long &b) {
    long long tmp = a;
    a = b;
    b = tmp;
}

void FindArrangementByInvertedSequenceOrder(long long *num_list, long long max_num, long long kth) {
    long long inverted_sequence[12] = {0}, remained = kth;
    for (long long i = 1; i <= max_num; i++)
        if (remained == 1) {
            break;
        } else {
            if (map[i] >= remained) {
                inverted_sequence[i] = (remained - 1) / map[i - 1];
                remained -= inverted_sequence[i] * map[i - 1];
                i = 1;
            }
        }
    for (long long i = 1; i <= max_num; i++)
        if (inverted_sequence[i] != 0)
            for (long long j = 0; j < inverted_sequence[i]; j++)
                Swap(num_list[max_num - i + 1 + j], num_list[max_num - i + 1 + j + 1]);
}

int main() {
    int zu_shu = 0;
    scanf("%d", &zu_shu);
    while (zu_shu--) {
        long long max_num = 0, kth = 0;
        scanf("%ld%ld", &max_num, &kth);
        long long *num_list = new long long[max_num + 1];
        for (long long i = 1; i <= max_num; i++)
            num_list[i] = i;
        FindArrangementByInvertedSequenceOrder(num_list, max_num, kth);
        for (long long i = 1; i < max_num; i++)
            printf("%ld ", num_list[i]);
        printf("%ld\n", num_list[max_num]);
    }
    return 0;
}