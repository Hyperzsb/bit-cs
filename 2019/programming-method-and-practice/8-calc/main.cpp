#include<stdio.h>
#include<string.h>

char *calaulate(char *num1, int length1, char *num2, int length2, char *ans, char opt, int flag) {
    if (opt == '+') {
        int jinWei = 0, index = length1, tmp = 0;
        ans[length1 + 1] = '\0';
        for (int i = 0; i < length2; i++) {
            tmp = (num1[length1 - 1 - i] - '0') + (num2[length2 - 1 - i] - '0') + jinWei;
            if (tmp < 10) {
                ans[index] = tmp + '0';
                jinWei = 0;
                index--;
            } else {
                ans[index] = (tmp - 10) + '0';
                jinWei = 1;
                index--;
            }
        }
        for (int i = 0; i < length1 - length2; i++) {
            tmp = (num1[length1 - length2 - 1 - i] - '0') + jinWei;
            if (tmp < 10) {
                ans[index] = tmp + '0';
                jinWei = 0;
                index--;
            } else {
                ans[index] = (tmp - 10) + '0';
                jinWei = 1;
                index--;
            }
        }
        if (jinWei == 1) {
            ans[index] = '1';
            return ans;
        } else
            return ans + 1;
    } else if (opt == '-') {
        int jinWei = 0, index = length1, tmp = 0;
        memset(ans, '0', length1 + 2);
        ans[length1 + 1] = '\0';
        for (int i = 0; i < length2; i++) {
            tmp = (num1[length1 - 1 - i] - '0') - (num2[length2 - 1 - i] - '0') - jinWei;
            if (tmp >= 0) {
                ans[index] = tmp + '0';
                jinWei = 0;
                index--;
            } else {
                ans[index] = (tmp + 10) + '0';
                jinWei = 1;
                index--;
            }
        }
        for (int i = 0; i < length1 - length2; i++) {
            tmp = (num1[length1 - length2 - 1 - i] - '0') - jinWei;
            if (tmp >= 0) {
                ans[index] = tmp + '0';
                jinWei = 0;
                index--;
            } else {
                ans[index] = (tmp + 10) + '0';
                jinWei = 1;
                index--;
            }
        }
        //printf("%s\n",ans);
        int isNotZero = -1;
        for (int i = 0; i < length1 + 1; i++)
            if (ans[i] != '0') {
                isNotZero = i;
                break;
            }
        if (isNotZero == -1) {
            ans[0] = '0';
            ans[1] = '\0';
            return ans;
        } else {
            if (flag) {
                return ans + isNotZero;
            } else {
                ans[isNotZero - 1] = '-';
                return ans + isNotZero - 1;
            }
        }
    } else {
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
}

int main() {
    char num1[100100], num2[100100], ans[200500], opt = '\0', tmp = '\0';
    int index1 = 0, index2 = 0, flag = 1;
    while (~scanf("%c", &tmp)) {
        if (tmp != '\n') {
            if (tmp == ' ')
                continue;
            if (tmp == '+' || tmp == '-' || tmp == '*') {
                opt = tmp;
                flag = 0;
                continue;
            }
            if (flag) {
                num1[index1] = tmp;
                index1++;
            } else {
                num2[index2] = tmp;
                index2++;
            }
        } else {
            num1[index1] == '\0';
            num2[index2] == '\0';
            if ((index1 == 1 && num1[0] == '0' && opt == '*') || (index2 == 1 && num2[0] == '0' && opt == '*')) {
                printf("0\n");
                index1 = 0;
                index2 = 0;
                flag = 1;
                continue;
            }
            if (index1 > index2)
                printf("%s\n", calaulate(num1, index1, num2, index2, ans, opt, 1));
            else {
                if (index1 == index2 && strcmp(num1, num2) >= 0) {
                    printf("%s\n", calaulate(num1, index1, num2, index2, ans, opt, 1));
                } else {
                    printf("%s\n", calaulate(num2, index2, num1, index1, ans, opt, 0));
                }
            }
            index1 = 0;
            index2 = 0;
            flag = 1;
            continue;
        }
    }
    return 0;
}
