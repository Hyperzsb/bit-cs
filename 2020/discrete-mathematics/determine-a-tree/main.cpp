#include <cstdio>

void dfs(int **map, int *flag, int depth, int point_num) {
    flag[depth] = 1;
    for (int i = 0; i < point_num; i++)
        if (map[depth][i] == 1 && flag[i] == 0)
            dfs(map, flag, i, point_num);
}

int main() {
    int point_num = 0;
    scanf("%d", &point_num);

    int **map = new int *[point_num];
    int *flag = new int[point_num];
    for (int i = 0; i < point_num; i++) {
        map[i] = new int[point_num];
        flag[i] = 0;
    }

    for (int i = 0; i < point_num; i++)
        for (int j = 0; j < point_num; j++) {
            scanf("%d", &map[i][j]);
            if (map[i][j] > 1 || map[i][j] < 0) {
                printf("no\n");
                return 0;
            }
        }

    int line_num = 0;
    for (int i = 0; i < point_num; i++)
        for (int j = i; j < point_num; j++)
            if (map[i][j] != map[j][i]) {
                printf("no\n");
                return 0;
            } else {
                line_num += map[i][j];
            }

    if (line_num != point_num - 1) {
        printf("no\n");
        return 0;
    }

    dfs(map, flag, 0, point_num);
    for (int i = 0; i < point_num; i++)
        if (flag[i] != 1) {
            printf("no\n");
            return 0;
        }

    printf("yes\n");

    return 0;
}