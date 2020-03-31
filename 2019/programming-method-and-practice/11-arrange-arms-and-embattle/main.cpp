#include<stdio.h>
#include<malloc.h>
#include<algorithm>

bool cmp(int a, int b) {
    return a < b;
}

int main() {
    int renShu = 0;
    long long int ans = 0;
    scanf("%d", &renShu);
    int *xList = (int *) malloc((renShu + 5) * sizeof(int));
    int *yList = (int *) malloc((renShu + 5) * sizeof(int));
    for (int i = 0; i < renShu; i++)
        scanf("%d%d", &xList[i], &yList[i]);
    std::sort(xList, xList + renShu, cmp);
    std::sort(yList, yList + renShu, cmp);
    for (int i = 0; i < renShu; i++)
        xList[i] -= i;
    std::sort(xList, xList + renShu, cmp);
    for (int i = 0; i < renShu / 2; i++)
        ans += yList[renShu - 1 - i] - yList[i] + xList[renShu - 1 - i] - xList[i];
    printf("%lld\n", ans);
    return 0;
}