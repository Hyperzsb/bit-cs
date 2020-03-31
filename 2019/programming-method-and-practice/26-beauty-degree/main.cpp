#include<stdio.h>
#include<stdlib.h>
#include<algorithm>

#define MINIMUM -0x3f3f3f3f

int main() {
    long long int renShu = 0, max = MINIMUM;
    scanf("%lld", &renShu);
    long long int *numList = (long long int *) malloc((renShu + 10) * sizeof(long long int));
    long long int **dp = (long long int **) malloc(5 * sizeof(long long int *));
    for (int i = 0; i < 3; i++) {
        dp[i] = (long long int *) malloc((renShu + 10) * sizeof(long long int));
        for (int j = 0; j < renShu; j++)
            dp[i][j] = MINIMUM;
    }

    for (int i = 0; i < renShu; i++)
        scanf("%lld", &numList[i]);

    dp[0][0] = numList[0];
    for (int i = 1; i < renShu; i++)
        dp[0][i] = std::max(numList[i], numList[i] + dp[0][i - 1]);

    for (int i = 1; i < 3; i++) {
        max = MINIMUM;
        for (int j = 1; j < renShu; j++) {
            max = std::max(max, dp[i - 1][j - 1]);
            dp[i][j] = std::max(max, dp[i][j - 1]) + numList[j];
        }
    }
    max = MINIMUM;
    for (int i = 0; i < renShu; i++)
        max = std::max(max, dp[2][i]);
    printf("%lld\n", max);
    return 0;
}