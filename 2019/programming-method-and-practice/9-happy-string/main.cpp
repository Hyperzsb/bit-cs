#include<stdio.h>
#include<string.h>

int main() {
    int zuShu = 0, length = 0, tmp[5] = {0}, flag = 1;
    char str[2000] = {'\0'}, sample[] = "fattyhappy";
    scanf("%d", &zuShu);
    int i = 0;
    for (; i < zuShu; i++) {
        memset(str, '\0', 2000);
        scanf("%s", str);
        length = strlen(str);
        int j = 0;
        for (; j < length - 9; j++) {
            int flag1 = 0, flag2 = 0;
            int k = 0;
            for (; k < 10; k++) {
                if (flag1 > 2) {
                    flag2 = 1;
                    break;
                }
                if (str[k + j] != sample[k]) {
                    tmp[flag1] = k + j;
                    flag1++;
                }
            }
            if (flag2)
                continue;
            else {
                if (flag1 == 0) {
                    printf("%d %d\n", j + 2, j + 7);
                    flag = 0;
                    break;
                } else if (flag1 == 1) {
                    int k = 0, tmpFlag = 0;
                    for (; k < length; k++)
                        if ((k < j || k > j + 9) && str[k] == sample[tmp[0] - j]) {
                            if (k + 1 < tmp[0] + 1)
                                printf("%d %d\n", k + 1, tmp[0] + 1);
                            else
                                printf("%d %d\n", tmp[0] + 1, k + 1);
                            tmpFlag = 1;
                            flag = 0;
                            break;
                        }
                    if (tmpFlag)
                        break;
                    continue;
                } else if (str[tmp[0]] == sample[tmp[1] - j] && str[tmp[1]] == sample[tmp[0] - j]) {
                    printf("%d %d\n", tmp[0] + 1, tmp[1] + 1);
                    flag = 0;
                    break;
                } else
                    continue;
            }
        }
        if (flag)
            printf("-1\n");
        else
            flag = 1;
    }
    return 0;
}