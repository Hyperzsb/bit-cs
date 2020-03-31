#include<stdio.h>

int charsNum[100000][3] = {0};
unsigned char chars[100000][4] = {'\0'};

int main() {
    int i = 0, flag = 1;
    unsigned int num = 0, tmp = 0, tmpList[5] = {'\0'};
    unsigned char wei[5] = {'\0'};
    while (scanf("%c", &wei[0]) != EOF) {
        tmp = wei[0];
        if (192 <= tmp && tmp <= 223) {
            scanf("%c", &wei[1]);
            tmpList[0] = wei[0];
            tmpList[1] = wei[1];
            num = (tmpList[0] - 128 - 64) * 64 + tmpList[1] - 128;
            chars[num][0] = wei[0];
            chars[num][1] = wei[1];
            charsNum[num][1] = 2;
            charsNum[num][0]++;
        } else if (tmp > 223) {
            scanf("%c%c", &wei[1], &wei[2]);
            tmpList[0] = wei[0];
            tmpList[1] = wei[1];
            tmpList[2] = wei[2];
            num = (tmpList[0] - 128 - 64 - 32) * 64 * 64 + (tmpList[1] - 128) * 64 + tmpList[2] - 128;
            chars[num][0] = wei[0];
            chars[num][1] = wei[1];
            chars[num][2] = wei[2];
            charsNum[num][1] = 3;
            charsNum[num][0]++;
        } else
            continue;
    }
    i = 0;
    for (; i < 100000; i++)
        if (charsNum[i][0] > 1) {
            flag = 0;
            if (charsNum[i][1] == 2)
                printf("%c%c 0x%04x %d\n", chars[i][0], chars[i][1], i, charsNum[i][0]);
            else
                printf("%c%c%c 0x%04x %d\n", chars[i][0], chars[i][1], chars[i][2], i, charsNum[i][0]);
        }
    if (flag)
        printf("No repeat!\n");
    return 0;
}