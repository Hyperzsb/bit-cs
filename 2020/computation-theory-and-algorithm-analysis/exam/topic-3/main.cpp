#include <cstdio>

int map[25][25] = {1};
int flag[25] = {0};
int ans = 0;
int current = 0;
int ox_num = 0;
int v_num = 0;

void clique(int index) {
    if (index > ox_num) {
        if (current > ans)
            ans = current;
        return;
    }
    int tmp_flag = 1;
    for (int i = 1; i < index; i++)
        if (flag[i] == 1 && map[i][index] == 0)
            tmp_flag = 0;
    if (tmp_flag) {
        flag[index] = 1;
        current++;
        clique(index + 1);
        current--;
        flag[index] = 0;
    }
    if (current + ox_num - index > ans)
        clique(index + 1);
}

int main() {
    scanf("%d%d", &ox_num, &v_num);
    for (int i = 0; i < v_num; i++) {
        int a = 0, b = 0;
        scanf("%d%d", &a, &b);
        map[a][b] = 1;
        map[b][a] = 1;
    }

    for (int i = 1; i <= ox_num; i++) {
        for (int j = 1; j <= ox_num; j++)
            map[i][j] = 1 - map[i][j];
    }

    clique(1);
    printf("%d\n", ans);

    return 0;
}
