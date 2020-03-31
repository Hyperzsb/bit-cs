#include<stdio.h>
#include<memory.h>
#include<queue>

int map[103][103][53];

int bfs(int sX, int sY, int eX, int eY, int col, int row, int jianGe) {
    std::queue<int> Q;
    Q.push(sX);
    Q.push(sY);
    Q.push(0);
    Q.push(0);
    map[sX][sY][0] = 1;
    while (!Q.empty()) {
        int x = Q.front();
        Q.pop();
        int y = Q.front();
        Q.pop();
        int time = Q.front();
        Q.pop();
        int ans = Q.front();
        Q.pop();
        int flag = (time + 1) % jianGe;
        if (x == eX && y == eY)
            return ans;
        if (x - 1 >= 0 && map[x - 1][y][flag] == 0) {
            Q.push(x - 1);
            Q.push(y);
            Q.push(time + 1);
            Q.push(ans + 1);
            map[x - 1][y][flag] = 1;
        }
        if (y + 1 < row && map[x][y + 1][flag] == 0) {
            Q.push(x);
            Q.push(y + 1);
            Q.push(time + 1);
            Q.push(ans + 1);
            map[x][y + 1][flag] = 1;
        }
        if (x + 1 < col && map[x + 1][y][flag] == 0) {
            Q.push(x + 1);
            Q.push(y);
            Q.push(time + 1);
            Q.push(ans + 1);
            map[x + 1][y][flag] = 1;
        }
        if (y - 1 >= 0 && map[x][y - 1][flag] == 0) {
            Q.push(x);
            Q.push(y - 1);
            Q.push(time + 1);
            Q.push(ans + 1);
            map[x][y - 1][flag] = 1;
        }
    }
    return -1;
}

int main() {
    int zuShu = 0;
    scanf("%d", &zuShu);
    while (zuShu--) {
        memset(map, 0, 103 * 103 * 53);
        int col = 0, row = 0, jianGe = 0, start[2] = {0}, end[2] = {0};
        char tmpStr[103];
        scanf("%d%d%d", &col, &row, &jianGe);
        for (int i = 0; i < col; i++) {
            scanf("%s", tmpStr);
            for (int j = 0; j < row; j++)
                if (tmpStr[j] == '.')
                    for (int k = 0; k < jianGe; k++)
                        map[i][j][k] = 0;
                else if (tmpStr[j] == '#')
                    for (int k = 0; k < jianGe; k++)
                        map[i][j][k] = 2;
                else if (tmpStr[j] == '*')
                    for (int k = 0; k < jianGe; k++)
                        if (k == 0)
                            map[i][j][k] = 0;
                        else
                            map[i][j][k] = 2;
                else if (tmpStr[j] == 'S') {
                    start[0] = i;
                    start[1] = j;
                } else if (tmpStr[j] == 'E') {
                    end[0] = i;
                    end[1] = j;
                }
        }
        printf("%d\n", bfs(start[0], start[1], end[0], end[1], col, row, jianGe));
    }

    return 0;
}