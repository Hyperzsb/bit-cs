#include<stdio.h>

long long int dp[2010][2010] = {0}, startList[2010] = {0}, ans = 0;

int main() {
    int geShu = 0, start = 0, end = 0;
    scanf("%d", &geShu);
    scanf("%d%d", &end, &start);
    dp[1][end] = 1, startList[1] = start;
    for (int i = 2; i <= geShu; i++) {
        scanf("%d", &start);
        startList[i] = start;
        for (int j = 1; j < 2010; j++) {
            if (dp[i - 1][j] != 0)
                if (startList[i - 1] < startList[i]) {
                    if (j < startList[i - 1]) {
                        dp[i][j] += dp[i - 1][j];
                        dp[i][j] %= 2147483647;
                    } else if (j > startList[i - 1] && j < startList[i]) {
                        dp[i][startList[i - 1]] += dp[i - 1][j];
                        dp[i][startList[i - 1]] %= 2147483647;
                    } else {
                        dp[i][j] += dp[i - 1][j];
                        dp[i][j] %= 2147483647;
                        dp[i][startList[i - 1]] += dp[i - 1][j];
                        dp[i][startList[i - 1]] %= 2147483647;
                    }
                } else {
                    if (j < startList[i]) {
                        dp[i][j] += dp[i - 1][j];
                        dp[i][j] %= 2147483647;
                        dp[i][startList[i - 1]] += dp[i - 1][j];
                        dp[i][startList[i - 1]] %= 2147483647;
                    } else if (j < startList[i - 1] && j > startList[i]) {
                        dp[i][startList[i - 1]] += dp[i - 1][j];
                        dp[i][startList[i - 1]] %= 2147483647;
                    } else {
                        dp[i][j] += dp[i - 1][j];
                        dp[i][j] %= 2147483647;
                    }
                }
        }
    }
    for (int i = 1; i < 2010; i++) {
        ans += dp[geShu][i];
        ans %= 2147483647;
    }
    printf("%lld\n", ans);
    return 0;
}