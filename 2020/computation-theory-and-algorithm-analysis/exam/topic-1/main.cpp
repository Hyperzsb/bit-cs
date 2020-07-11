#include <cstdio>
#include <algorithm>

using std::sort;

struct eagle {
    int wingspan;
    int body_height;
    int leg_height;
    int neighbor_num;
    int neighbor_list[505];
};

bool compare(int a, int b) {
    return a > b;
}

int dfs(int index, eagle *eagle_list, int *dp) {
    if (dp[index] != 0) {
        return dp[index];
    } else {
        dp[index] = eagle_list[index].body_height;
        for (int i = 0; i < eagle_list[index].neighbor_num; i++)
            if (eagle_list[index].wingspan > eagle_list[eagle_list[index].neighbor_list[i]].wingspan) {
                int tmp = dfs(eagle_list[index].neighbor_list[i], eagle_list, dp) + eagle_list[index].body_height;
                if (tmp > dp[index])
                    dp[index] = tmp;
            }
        return dp[index];
    }
}

int main() {
    eagle eagle_list[505];
    int dp[505] = {0};
    int t = 0;
    scanf("%d", &t);
    while (t--) {
        for (int i = 0; i < 505; i++) {
            eagle_list[i].neighbor_num = 0;
            dp[i] = 0;
        }

        int eagle_num = 0;
        scanf("%d", &eagle_num);
        for (int i = 1; i <= eagle_num; i++) {
            scanf("%d%d%d", &eagle_list[i].wingspan, &eagle_list[i].body_height, &eagle_list[i].leg_height);
            int neighbor_num = 0;
            scanf("%d", &neighbor_num);
            for (int j = 0; j < neighbor_num; j++) {
                int neighbor = 0;
                scanf("%d", &neighbor);
                eagle_list[i].neighbor_list[eagle_list[i].neighbor_num++] = neighbor;
                eagle_list[neighbor].neighbor_list[eagle_list[neighbor].neighbor_num++] = i;
            }
        }

        for (int i = 1; i <= eagle_num; i++)
            dfs(i, eagle_list, dp);

        for (int i = 1; i <= eagle_num; i++)
            dp[i] += eagle_list[i].leg_height;

        sort(dp + 1, dp + 1 + eagle_num, compare);
        printf("%d\n", dp[1]);
    }

    return 0;
}