#include<stdio.h>

int time[1000001] = {0};

int main() {
    int studentNum = 0, start = 0, end = 0, max = 0, tmp = 0;
    scanf("%d", &studentNum);
    for (int i = 0; i < studentNum; i++) {
        scanf("%d%d", &start, &end);
        time[start]++;
        time[end + 1]--;
    }
    for (int i = 0; i < 1000001; i++) {
        tmp += time[i];
        if (tmp > max)
            max = tmp;
    }
    printf("%d\n", max);
    return 0;
}