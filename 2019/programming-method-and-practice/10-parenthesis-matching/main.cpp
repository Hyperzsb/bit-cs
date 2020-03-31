#include<stdio.h>

int main() {
    long long int zuShu = 0, length = 0, legalNum = 0, num1 = 0, num2 = 0, ans = 0;
    scanf("%d", &zuShu);
    int legalList[100100][3] = {0};
    char tmpList[100100] = {'\0'}, tmpch;

    int i = 0;
    for (; i < zuShu; i++) {
        num1 = 0, num2 = 0;
        scanf("\n%c", &tmpch);
        while (tmpch != '\n') {
            tmpList[length] = tmpch;
            if (tmpch == '(') {
                num1++;
                length++;
            } else {
                if (length - 1 >= 0 && tmpList[length - 1] == '(') {
                    num1--;
                    length--;
                } else {
                    num2++;
                    length++;
                }
            }
            scanf("%c", &tmpch);
        }
        if (num1 != 0 && num2 != 0);
        else {
            if (num1 == 0 && num2 == 0) {
                if (legalList[0][0] > 0) {
                    ans++;
                    legalList[0][0]--;
                } else
                    legalList[0][0]++;
            } else if (num1 != 0) {
                if (legalList[num1][1] > 0) {
                    ans++;
                    legalList[num1][1]--;
                } else
                    legalList[num1][0]++;
            } else {
                if (legalList[num2][0] > 0) {
                    ans++;
                    legalList[num2][0]--;
                } else
                    legalList[num2][1]++;
            }
        }
        length = 0;
    }
    printf("%lld\n", ans);
    return 0;
}