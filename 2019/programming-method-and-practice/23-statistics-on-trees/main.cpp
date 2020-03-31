#include<stdio.h>
#include<vector>

using namespace std;
vector<int> map[200010];
vector<int> flag[200010];
int depthList[200010] = {0};
int size[200010] = {0};

int dfs(int index, int depth, int parent) {
    depthList[index] = depth;
    for (int i = 0; i < map[index].size(); i++) {
        if (map[index][i] == parent) {
            flag[index][i] = 1;
            if (map[index].size() == 1 && flag[index][0] == 1) {
                size[index] = 1;
                return 1;
            }
        } else if (flag[index][i] == 0) {
            flag[index][i] = 1;
            size[index] += dfs(map[index][i], depth + 1, index);
        }
    }
    size[index]++;
    return size[index];
}

int main() {
    long long int ans = 0, tmp1 = 0, tmp2 = 0;
    int geShu = 0, start = 0, end = 0, oddNum = 0;
    scanf("%d", &geShu);
    for (int i = 0; i < geShu - 1; i++) {
        scanf("%d%d", &start, &end);
        map[start - 1].push_back(end - 1);
        flag[start - 1].push_back(0);
        map[end - 1].push_back(start - 1);
        flag[end - 1].push_back(0);
    }
    dfs(0, 0, -1);
    for (int i = 1; i < geShu; i++) {
        tmp1 = size[i], tmp2 = geShu - size[i];
        ans += tmp1 * tmp2;
        if (depthList[i] % 2 == 1)
            oddNum++;
    }
    tmp1 = geShu - oddNum, tmp2 = oddNum;
    ans = (ans + tmp1 * tmp2) / 2;
    printf("%lld\n", ans);
    return 0;
}