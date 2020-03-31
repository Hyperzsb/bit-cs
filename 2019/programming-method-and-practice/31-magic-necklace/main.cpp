#include<stdio.h>
#include<stdlib.h>

int main() {
    int zuShu = 0, geShu = 0, maxE = 0;
    long long int ans = 0;
    scanf("%d", &zuShu);
    while (zuShu--) {
        scanf("%d%d", &geShu, &maxE);
        long long int **dp = (long long int **) malloc((geShu + 10) * sizeof(long long int *));
        for (int i = 0; i < geShu; i++)
            dp[i] = (long long int *) malloc((maxE + 10) * sizeof(long long int));
        for (int k = 0; k < maxE; k++) {
            for (int i = 0; i < maxE; i++)
                dp[0][i] = 0;
            dp[0][k] = 1;
            for (int i = 1; i < geShu; i++)
                for (int j = 0; j < maxE; j++) {
                    if (j == 0)
                        dp[i][j] = (dp[i - 1][j] + dp[i - 1][j + 1]) % 998244353;
                    else if (j == maxE - 1)
                        dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]) % 998244353;
                    else
                        dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j] + dp[i - 1][j + 1]) % 998244353;
                }
            if (k == 0) {
                ans = (ans + dp[geShu - 1][0]) % 998244353;
                ans = (ans + dp[geShu - 1][1]) % 998244353;
            } else if (k == maxE - 1) {
                ans = (ans + dp[geShu - 1][maxE - 1]) % 998244353;
                ans = (ans + dp[geShu - 1][maxE - 2]) % 998244353;
            } else {
                ans = (ans + dp[geShu - 1][k - 1]) % 998244353;
                ans = (ans + dp[geShu - 1][k]) % 998244353;
                ans = (ans + dp[geShu - 1][k + 1]) % 998244353;
            }
        }
        printf("%lld\n", ans);
        free(dp);
        ans = 0;
    }
    return 0;
}