#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

int minNum(int a, int b, int c) {
    int tmp = a < b ? a : b;
    tmp = tmp < c ? tmp : c;
    return tmp;
}

int dfs1(int *numList, int maxNum) {
    int flag = 1, *tmpList = (int *) malloc((maxNum + 10) * sizeof(int));
    for (int i = 1; i <= maxNum; i++)
        tmpList[i] = numList[i] % 3;
    for (int i = 1; i <= maxNum - 2; i++) {
        if (tmpList[i] != 0) {
            if (tmpList[i + 1] >= tmpList[i] && tmpList[i + 2] >= tmpList[i]) {
                tmpList[i + 1] -= tmpList[i];
                tmpList[i + 2] -= tmpList[i];
                tmpList[i] -= tmpList[i];
            } else {
                flag = 0;
                break;
            }
        }
    }
    return flag;
}

int *dfs2(int *numList, int maxNum, int *ans) {
    int flag = 0, *tmpList = (int *) malloc((maxNum + 10) * sizeof(int));
    for (int i = 1; i <= maxNum; i++)
        tmpList[i] = numList[i] % 3;
    for (int i = 1; i <= maxNum - 2; i++) {
        int tmp = minNum(tmpList[i], tmpList[i + 1], tmpList[i + 2]);
        for (int j = 0; j < 3; j++)
            tmpList[i + j] -= tmp;
    }
    for (int i = 1; i <= maxNum - 1; i++)
        if (tmpList[i] > 1) {
            ans[0] = 0;
            break;
        } else if (tmpList[i] == 1) {
            if (flag) {
                ans[0] = 0;
                break;
            } else {
                flag = 1;
                if (tmpList[i + 1] != 0) {
                    if (i == 1) {
                        ans[0] = 1;
                        ans[1] = i + 2;
                    } else if (i == maxNum - 1) {
                        ans[0] = 1;
                        ans[1] = i - 1;
                    } else {
                        ans[0] = 2;
                        ans[1] = i - 1;
                        ans[2] = i + 2;
                    }
                    tmpList[i]--;
                    tmpList[i + 1]--;
                } else if (tmpList[i + 2] != 0) {
                    ans[0] = 1;
                    ans[1] = i + 1;
                    tmpList[i]--;
                    tmpList[i + 2]--;
                } else {
                    ans[0] = 0;
                    break;
                }
            }
        } else
            continue;
    return ans;
}

int main() {
    int maxNum = 0, geShu = 0, pai = 0;
    scanf("%d%d", &maxNum, &geShu);
    int *numList = (int *) malloc((maxNum + 10) * sizeof(int));
    int *ansList = (int *) malloc((maxNum + 10) * sizeof(int));
    memset(numList, 0, sizeof(numList[0]) * (maxNum + 10));
    memset(ansList, 0, sizeof(ansList[0]) * (maxNum + 10));
    for (int i = 0; i < 3 * geShu + 1; i++) {
        scanf("%d", &pai);
        numList[pai]++;
    }
    for (int i = 1; i <= maxNum; i++) {
        if (numList[i] > 1) {
            numList[i]--;
            int flag = dfs1(numList, maxNum);
            if (flag)
                ansList[i] = 1;
            numList[i]--;
            int res[5] = {0};
            dfs2(numList, maxNum, res);
            if (res[0])
                for (int j = 0; j < res[0]; j++)
                    ansList[res[j + 1]] = 1;
            numList[i] += 2;
        } else if (numList[i] == 1) {
            numList[i]--;
            int flag = dfs1(numList, maxNum);
            if (flag)
                ansList[i] = 1;
            numList[i]++;
        } else
            continue;
    }
    int i = 1, tmpFlag = 1;
    for (; i <= maxNum; i++)
        if (ansList[i] == 1) {
            tmpFlag = 0;
            printf("%d", i);
            i++;
            break;
        }
    if (tmpFlag) {
        printf("NO\n");
        return 0;
    } else
        for (; i <= maxNum; i++)
            if (ansList[i] == 1)
                printf(" %d", i);
    printf("\n");
    return 0;
}