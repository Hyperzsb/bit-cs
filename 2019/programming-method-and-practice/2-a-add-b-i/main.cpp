#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main() {
    char num[2][100100] = {'\0'};
    int zuShu = 0;
    scanf("%d", &zuShu);
    for (int i = 0; i < zuShu; i++) {
        scanf("%s%s", num[0], num[1]);
        int length[2] = {0};
        for (int j = 0; j < 2; j++)
            length[j] = strlen(num[j]);
        int flag = length[0] > length[1] ? 0 : 1;
        char *resList = (char *) malloc((length[flag] + 1) * sizeof(char));
        memset(resList, '\0', length[flag] + 1);
        resList[0] = ' ';
        int jinWei = 0;
        for (int j = 0; j < length[1 - flag]; j++) {
            if ((num[flag][length[flag] - 1 - j] - '0') + (num[1 - flag][length[1 - flag] - 1 - j] - '0') + jinWei ==
                0) {
                resList[length[flag] - j] = '0';
                jinWei = 0;
                continue;
            }
            if ((num[flag][length[flag] - 1 - j] - '0') + (num[1 - flag][length[1 - flag] - 1 - j] - '0') + jinWei ==
                1) {
                resList[length[flag] - j] = '1';
                jinWei = 0;
                continue;
            }
            if ((num[flag][length[flag] - 1 - j] - '0') + (num[1 - flag][length[1 - flag] - 1 - j] - '0') + jinWei ==
                2) {
                resList[length[flag] - j] = '0';
                jinWei = 1;
                continue;
            }
            if ((num[flag][length[flag] - 1 - j] - '0') + (num[1 - flag][length[1 - flag] - 1 - j] - '0') + jinWei ==
                3) {
                resList[length[flag] - j] = '1';
                jinWei = 1;
                continue;
            }
        }
        for (int j = 0; j < length[flag] - length[1 - flag]; j++) {
            if ((num[flag][length[flag] - length[1 - flag] - 1 - j] - '0') + jinWei == 0) {
                resList[length[flag] - length[1 - flag] - j] = '0';
                jinWei = 0;
                continue;
            }
            if ((num[flag][length[flag] - length[1 - flag] - 1 - j] - '0') + jinWei == 1) {
                resList[length[flag] - length[1 - flag] - j] = '1';
                jinWei = 0;
                continue;
            }
            if ((num[flag][length[flag] - length[1 - flag] - 1 - j] - '0') + jinWei == 2) {
                resList[length[flag] - length[1 - flag] - j] = '0';
                jinWei = 1;
                continue;
            }
        }
        if (jinWei == 1)
            resList[0] = '1';
        if (jinWei) {
            for (int k = 0; k < length[flag] + 3 - length[0]; k++)
                printf(" ");
            printf("%s\n+", num[0]);
            for (int k = 0; k < length[flag] + 2 - length[1]; k++)
                printf(" ");
            printf("%s\n", num[1]);
            for (int k = 0; k < 3 + length[flag]; k++)
                printf("-");
            printf("\n  ");
            for (int k = 0; k < length[flag] + 1; k++)
                printf("%c", resList[k]);
            printf("\n");
        } else {
            for (int k = 0; k < length[flag] + 2 - length[0]; k++)
                printf(" ");
            printf("%s\n+", num[0]);
            for (int k = 0; k < length[flag] + 1 - length[1]; k++)
                printf(" ");
            printf("%s\n", num[1]);
            for (int k = 0; k < 2 + length[flag]; k++)
                printf("-");
            printf("\n ");
            for (int k = 0; k < length[flag] + 1; k++)
                printf("%c", resList[k]);
            printf("\n");
        }
    }
    return 0;
}