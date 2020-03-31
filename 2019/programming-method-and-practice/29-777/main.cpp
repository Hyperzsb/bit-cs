#include<stdio.h>
#include<string.h>

int add(char *num, int length, int nu) {
    int jinWei = 0;
    int tmp = nu + (num[0] - '0');
    if (tmp > 9) {
        jinWei = 1;
        num[0] = (tmp - 10) + '0';
        int i = 1;
        for (; i < length; i++) {
            tmp = jinWei + (num[i] - '0');
            if (tmp > 9) {
                jinWei = 1;
                num[i] = (tmp - 10) + '0';
            } else {
                jinWei = 0;
                num[i] = tmp + '0';
                break;
            }
        }
        if (jinWei == 1) {
            num[length] = '1';
            num[length + 1] = '\0';
            return length + 1;
        } else {
            num[length] = '\0';
            return length;
        }
    } else {
        num[0] = tmp + '0';
        num[length] = '\0';
        return length;
    }
}

void minus(char *num1, char *num2) {
    int length1 = strlen(num1), length2 = strlen(num2);
    int jieWei = 0, tmp = 0;
    int i = 0;
    for (; i < length2; i++) {
        tmp = (num1[i] - '0') - (num2[i] - '0') - jieWei;
        if (tmp >= 0) {
            jieWei = 0;
            num1[i] = tmp + '0';
        } else {
            jieWei = 1;
            num1[i] = (tmp + 10) + '0';
        }
    }
    for (i = length2; i < length1; i++) {
        tmp = (num1[i] - '0') - jieWei;
        if (tmp >= 0) {
            jieWei = 0;
            num1[i] = tmp + '0';
        } else {
            jieWei = 1;
            num1[i] = (tmp + 10) + '0';
        }
    }
    num1[length1] = '\0';
    for (i = 0; i < length1; i++) {
        if (num1[length1 - 1 - i] != '0')
            break;
        else if (num1[length1 - 1 - i] == '0' && i < (length1 - 1))
            num1[length1 - 1 - i] = '\0';
    }
    return;
}

int multiply(char *num, int length, int nu) {
    int len = length, jinWei = 0, tmp = 0;
    len = add(num, length, nu);
    int i = 0;
    for (; i < len; i++) {
        tmp = 9 * (num[i] - '0') + jinWei;
        if (tmp > 9) {
            jinWei = tmp / 10;
            num[i] = (tmp % 10) + '0';
        } else {
            jinWei = 0;
            num[i] = tmp + '0';
        }
    }
    if (jinWei != 0) {
        num[len] = jinWei + '0';
        num[len + 1] = '\0';
        return len + 1;
    } else {
        num[len] = '\0';
        return len;
    }
}

void no7Num(int index, char *num, int length, char *ans, int *flagList) {
    int len = 1, flag = 0;
    memset(ans, '0', length * sizeof(ans[0]));
    int i = 0;
    for (; i < length - 1; i++)
        if ((num[i] - '0') > 7) {
            len = multiply(ans, len, (num[i] - '0') - 1);
        } else if ((num[i] - '0') == 7) {
            flag = 1;
            len = multiply(ans, len, (num[i] - '0'));
            int j = i + 1;
            for (; j < length; j++)
                num[j] = '0';
        } else {
            len = multiply(ans, len, (num[i] - '0'));
        }
    if ((num[length - 1] - '0') > 7)
        add(ans, len, (num[length - 1] - '0') - 1);
    else if ((num[length - 1] - '0') == 7) {
        flag = 1;
        add(ans, len, num[length - 1] - '0');
    } else
        add(ans, len, num[length - 1] - '0');
    if (flag) {
        minus(ans, "1");
        flagList[index] = 1;
    }
    return;
}

int main() {
    int zuShu = 0, length1 = 0, length2 = 0, flagList[3] = {0};
    char start[10010], end[10010], tmp1[10010], tmp2[10010], ans1[10010], ans2[10010], tmp = '0';
    scanf("%d", &zuShu);
    while (zuShu--) {
        scanf("%s%s", start, end);
        strcpy(tmp1, start);
        strcpy(tmp2, end);
        length1 = strlen(start), length2 = strlen(end);
        no7Num(0, tmp1, length1, ans1, flagList);
        int i = 0;
        for (; i < length1 / 2; i++) {
            tmp = start[i];
            start[i] = start[length1 - 1 - i];
            start[length1 - 1 - i] = tmp;
        }
        minus(start, ans1);
        no7Num(1, tmp2, length2, ans2, flagList);
        for (i = 0; i < length2 / 2; i++) {
            tmp = end[i];
            end[i] = end[length2 - 1 - i];
            end[length2 - 1 - i] = tmp;
        }
        minus(end, ans2);
        minus(end, start);
        int lenAns = strlen(end);
        if (flagList[0])
            lenAns = add(end, lenAns, 1);
        for (i = 0; i < lenAns; i++)
            printf("%c", end[lenAns - 1 - i]);
        printf("\n");
        memset(flagList, 0, 3 * sizeof(flagList[0]));
    }
    return 0;
}