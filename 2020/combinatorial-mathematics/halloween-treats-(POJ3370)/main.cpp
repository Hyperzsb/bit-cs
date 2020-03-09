#include <cstdio>
#include <cstring>

long candy_list[100010], sum_list[100010], mod_list[100010];

int main() {
    long child_num = 0, family_num = 0;
    scanf("%ld%ld", &child_num, &family_num);
    while (child_num && family_num) {
        int flag = 0;
        for (long i = 1; i < child_num; i++)
            mod_list[i] = -1;
        mod_list[0] = 0;
        sum_list[0] = 0;
        for (long i = 1; i <= family_num; i++) {
            scanf("%ld", &candy_list[i]);
            sum_list[i] = (sum_list[i - 1] + candy_list[i]) % child_num;
        }
        for (long i = 1; i <= family_num; i++) {
            if (mod_list[sum_list[i]] != -1) {
                for (long j = mod_list[sum_list[i]] + 1; j < i; j++)
                    printf("%ld ", j);
                printf("%ld\n", i);
                flag = 1;
                break;
            } else {
                mod_list[sum_list[i]] = i;
            }
        }
        if (flag == 0)
            printf("no sweets\n");
        scanf("%ld%ld", &child_num, &family_num);
    }
    return 0;
}
