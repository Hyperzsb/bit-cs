#include<stdio.h>

int main() {
    int treeNum = 0, maxPeaches = 0, day = 0, num = 0, flag[2] = {0}, ans = 0;
    scanf("%d%d", &treeNum, &maxPeaches);
    int flagList[3003] = {0};
    int peachList[3003] = {0};
    for (int i = 0; i < treeNum; i++) {
        scanf("%d%d", &day, &num);
        flagList[day] = 1;
        peachList[day] += num;
    }
    for (int i = 0; i < 3003; i++) {
        if (flagList[i] == 1) {
            if (flag[0] == i - 1) {
                if ((peachList[i] + flag[1]) < maxPeaches) {
                    ans += peachList[i] + flag[1];
                } else {
                    ans += maxPeaches;
                    flag[0] = i;
                    if (flag[1] > maxPeaches)
                        flag[1] = peachList[i];
                    else
                        flag[1] = peachList[i] + flag[1] - maxPeaches;
                }
            } else {
                if (peachList[i] < maxPeaches)
                    ans += peachList[i];
                else {
                    ans += maxPeaches;
                    flag[0] = i;
                    flag[1] = peachList[i] - maxPeaches;
                }
            }
        } else {
            if ((flag[0] == i - 1) && (flag[1] > 0))
                if (flag[1] < maxPeaches)
                    ans += flag[1];
                else
                    ans += maxPeaches;
        }
    }
    printf("%d\n", ans);
    return 0;
}