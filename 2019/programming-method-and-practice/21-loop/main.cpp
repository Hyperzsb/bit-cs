#include<stdio.h>
#include<queue>

int map[1010][1010] = {0};

int bfs(int sX, int sY, int eX, int eY, int col, int row, int buChang) {
    std::queue<int> Q;
    Q.push(sX);
    Q.push(sY);
    Q.push(0);
    map[sX][sY] = 1;
    while (!Q.empty()) {
        int x = Q.front();
        Q.pop();
        int y = Q.front();
        Q.pop();
        int ans = Q.front();
        Q.pop();
        if (x == eX && y == eY)
            return ans;
        for (int i = 1; i <= buChang; i++) {
            if (x - i < 0 || map[x - i][y] == 2)
                break;
            else if (x - i >= 0 && map[x - i][y] == 1)
                continue;
            else if (x - i >= 0 && map[x - i][y] == 0) {
                Q.push(x - i);
                Q.push(y);
                Q.push(ans + 1);
                map[x - i][y] = 1;
            }
        }
        for (int i = 1; i <= buChang; i++) {
            if (y + i >= row || map[x][y + i] == 2)
                break;
            else if (y + i < row && map[x][y + i] == 1)
                continue;
            else if (y + i < row && map[x][y + i] == 0) {
                Q.push(x);
                Q.push(y + i);
                Q.push(ans + 1);
                map[x][y + i] = 1;
            }
        }
        for (int i = 1; i <= buChang; i++) {
            if (x + i >= col || map[x + i][y] == 2)
                break;
            else if (x + i < col && map[x + i][y] == 1)
                continue;
            else if (x + i < col && map[x + i][y] == 0) {
                Q.push(x + i);
                Q.push(y);
                Q.push(ans + 1);
                map[x + i][y] = 1;
            }
        }
        for (int i = 1; i <= buChang; i++) {
            if (y - i < 0 || map[x][y - i] == 2)
                break;
            else if (y - i >= 0 && map[x][y - i] == 1)
                continue;
            else if (y - i >= 0 && map[x][y - i] == 0) {
                Q.push(x);
                Q.push(y - i);
                Q.push(ans + 1);
                map[x][y - i] = 1;
            }
        }
    }
    return -1;
}

int main() {
    int col = 0, row = 0, buChang = 0, start[2] = {0}, end[2] = {0};
    char tmpStr[1010];
    scanf("%d%d%d", &col, &row, &buChang);
    for (int i = 0; i < col; i++) {
        scanf("%s", tmpStr);
        for (int j = 0; j < row; j++)
            if (tmpStr[j] == '.')
                map[i][j] = 0;
            else
                map[i][j] = 2;
    }
    scanf("%d%d%d%d", &start[0], &start[1], &end[0], &end[1]);
    printf("%d\n", bfs(start[0] - 1, start[1] - 1, end[0] - 1, end[1] - 1, col, row, buChang));
    return 0;
}