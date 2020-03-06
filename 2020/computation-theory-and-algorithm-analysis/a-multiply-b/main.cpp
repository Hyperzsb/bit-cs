#include<stdio.h>
#include<string.h>

char *calaulate(char *num1, int length1, char *num2, int length2, char *ans) {
    int jinWei = 0, index = length1 + length2 - 1, tmp = 0;
    memset(ans, '0', length1 + length2);
    ans[length1 + length2] = '\0';
    for (int i = length2 - 1; i >= 0; i--) {
        for (int j = length1 - 1; j >= 0; j--) {
            tmp = (num1[j] - '0') * (num2[i] - '0') + (ans[index - (length1 - 1 - j)] - '0') + jinWei;
            if (tmp < 10) {
                ans[index - (length1 - 1 - j)] = tmp + '0';
                jinWei = 0;
            } else {
                ans[index - (length1 - 1 - j)] = (tmp % 10) + '0';
                jinWei = tmp / 10;
            }
        }
        if (jinWei > 0)
            ans[index - length1] = jinWei + '0';
        jinWei = 0;
        index--;
    }
    if (ans[0] == '0')
        return ans + 1;
    else
        return ans;
}

int main() {
    char num1[100100], num2[100100], ans[200500];
    scanf("%s%s", num1, num2);
    int length1 = strlen(num1), length2 = strlen(num2);
    if ((length1 == 1 && num1[0] == '0') || (length2 == 1 && num2[0] == '0'))
        printf("0\n");
    if (length1 > length2)
        printf("%s\n", calaulate(num1, length1, num2, length2, ans));
    else {
        if (length1 == length2 && strcmp(num1, num2) >= 0) {
            printf("%s\n", calaulate(num1, length1, num2, length2, ans));
        } else {
            printf("%s\n", calaulate(num2, length2, num1, length1, ans));
        }
    }
    return 0;
}