#include<stdio.h>
#include<stdlib.h>

int main() {
    int geShu = 0, V = 0;
    scanf("%d%d", &geShu, &V);
    int *vList = (int *) malloc((geShu + 10) * sizeof(int));
    int **dp = (int **) malloc((geShu + 10) * sizeof(int *));
    for (int i = 0; i < geShu; i++) {
        dp[i] = (int *) malloc((V + 10) * sizeof(int));
        for (int j = 0; j < V + 10; j++)
            dp[i][j] = 0;
        scanf("%d", &vList[i]);
        dp[i][vList[i] % V] = 1;
    }
    for (int i = 1; i < geShu; i++)
        for (int j = 0; j < V; j++) {
            dp[i][j] += (dp[i - 1][j] + dp[i - 1][(j + V - vList[i] % V) % V]);
            dp[i][j] %= 10000000;
        }
    printf("%d\n", dp[geShu - 1][0]);
    return 0;
}