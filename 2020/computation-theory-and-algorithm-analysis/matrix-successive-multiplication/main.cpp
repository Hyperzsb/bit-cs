#include <cstdio>

int matrix[105] = {0}, dp[105][105] = {0}, break_point[105][105] = {0};

void Print(int start, int end) {
    if (start == end) {
        printf("A%d", start);
    } else {
        printf("(");
        Print(start, break_point[start][end]);
        Print(break_point[start][end] + 1, end);
        printf(")");
    }
}

int main() {
    int matrix_num = 0;
    scanf("%d", &matrix_num);
    for (int i = 0; i <= matrix_num; i++) {
        scanf("%d", &matrix[i]);
        dp[i][i] = 0;
    }
    for (int i = 1; i < matrix_num; i++)
        for (int j = 1; j < matrix_num - i + 1; j++) {
            int end = j + i;
            break_point[j][end] = j;
            dp[j][end] = dp[j][j] + dp[j + 1][end] + matrix[j - 1] * matrix[j] * matrix[end];
            for (int k = j + 1; k < end; k++) {
                int tmp = dp[j][k] + dp[k + 1][end] + matrix[j - 1] * matrix[k] * matrix[end];
                if (tmp < dp[j][end]) {
                    dp[j][end] = tmp;
                    break_point[j][end] = k;
                }
            }
        }
    printf("%d\n", dp[1][matrix_num]);
    if (matrix_num == 1) {
        printf("(A1)\n");
    } else {
        Print(1, matrix_num);
        printf("\n");
    }
    return 0;
}