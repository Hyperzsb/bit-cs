#include<stdio.h>
#include<stdlib.h>

int cmp(const void *a, const void *b) {
    return (*(long long *) a - *(long long *) b);
}

int main() {
    int zuShu = 0, geShu = 0;
    long long int ans = 0;
    scanf("%d", &zuShu);
    int i = 0;
    for (; i < zuShu; i++) {
        scanf("%d", &geShu);
        if (geShu == 0) {
            int noUse = 0;
            scanf("%d", &noUse);
            printf("0\n");
            continue;
        }
        long long *lengthList = (long long *) malloc((geShu + 5) * sizeof(long long));
        long long int *tmpList = (long long int *) malloc((geShu + 5) * sizeof(long long int));
        int j = 0;
        for (; j < geShu; j++) {
            scanf("%lld", &lengthList[j]);
            tmpList[j] = 0;
        }
        qsort(lengthList, geShu, sizeof(lengthList[0]), cmp);
        int index = 0, front = 0, back = 0;
        while (geShu - index + back - front > 1) {
            if (back - front == 0) {
                tmpList[back] = lengthList[index] + lengthList[index + 1];
                ans += tmpList[back];
                back++;
                index += 2;
            } else if (back - front == 1) {
                if (geShu - index >= 2) {
                    if (tmpList[front] >= lengthList[index + 1]) {
                        tmpList[back] = lengthList[index] + lengthList[index + 1];
                        ans += tmpList[back];
                        back++;
                        index += 2;
                    } else {
                        tmpList[back] = lengthList[index] + tmpList[front];
                        ans += tmpList[back];
                        back++;
                        front++;
                        index++;
                    }
                } else if (geShu - index == 1) {
                    tmpList[back] = lengthList[index] + tmpList[front];
                    ans += tmpList[back];
                    back++;
                    front++;
                    index++;
                } else
                    break;
            } else {
                if (geShu - index >= 2) {
                    if (tmpList[front] >= lengthList[index + 1]) {
                        tmpList[back] = lengthList[index] + lengthList[index + 1];
                        ans += tmpList[back];
                        index += 2;
                        back++;
                    } else if (tmpList[front + 1] < lengthList[index]) {
                        tmpList[back] = tmpList[front] + tmpList[front + 1];
                        ans += tmpList[back];
                        back++;
                        front += 2;
                    } else if (tmpList[front] < lengthList[index + 1] && tmpList[front + 1] >= lengthList[index]) {
                        tmpList[back] = tmpList[front] + lengthList[index];
                        ans += tmpList[back];
                        front++;
                        back++;
                        index++;
                    }
                } else if (geShu - index == 1) {
                    if (lengthList[index] > tmpList[front + 1]) {
                        tmpList[back] = tmpList[front] + tmpList[front + 1];
                        ans += tmpList[back];
                        back++;
                        front += 2;
                    } else {
                        tmpList[back] = lengthList[index] + tmpList[front];
                        ans += tmpList[back];
                        back++;
                        front++;
                        index++;
                    }
                } else {
                    tmpList[back] = tmpList[front] + tmpList[front + 1];
                    ans += tmpList[back];
                    back++;
                    front += 2;
                }
            }
        }
        printf("%lld\n", ans);
        ans = 0;
        free(lengthList);
        free(tmpList);
    }
    return 0;
}