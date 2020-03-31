#include<stdio.h>
#include<memory.h>
#include<algorithm>

#define MAX INFINITY
char map[17][17];
int solution[6][7];

void reRot(int index) {
    char tmpMap[5][5] = {'\0'};
    for (int i = (index / 4) * 4, k = 0; i < (index / 4 + 1) * 4; i++, k++)
        for (int j = (index % 4) * 4, h = 0; j < (index % 4 + 1) * 4; j++, h++)
            tmpMap[k][h] = map[i][j];
    for (int i = (index / 4) * 4, k = 0; i < (index / 4 + 1) * 4; i++, k++)
        for (int j = (index % 4) * 4, h = 0; j < (index % 4 + 1) * 4; j++, h++)
            map[i][j] = tmpMap[3 - h][k];
}

void rot(int index) {
    char tmpMap[5][5] = {'\0'};
    for (int i = (index / 4) * 4, k = 0; i < (index / 4 + 1) * 4; i++, k++)
        for (int j = (index % 4) * 4, h = 0; j < (index % 4 + 1) * 4; j++, h++)
            tmpMap[k][h] = map[i][j];
    for (int i = (index / 4) * 4, k = 0; i < (index / 4 + 1) * 4; i++, k++)
        for (int j = (index % 4) * 4, h = 0; j < (index % 4 + 1) * 4; j++, h++)
            map[i][j] = tmpMap[h][3 - k];
}

bool isLegal(int index) {
    bool ans = true;
    int flagList[16] = {0};
    for (int i = 0; i < 4; i++) {
        memset(flagList, 0, 16 * sizeof(flagList[0]));
        for (int j = 0; j < (index % 4 + 1) * 4; j++) {
            if (map[(index / 4) * 4 + i][j] == '0')
                flagList[0]++;
            else if (map[(index / 4) * 4 + i][j] == '1')
                flagList[1]++;
            else if (map[(index / 4) * 4 + i][j] == '2')
                flagList[2]++;
            else if (map[(index / 4) * 4 + i][j] == '3')
                flagList[3]++;
            else if (map[(index / 4) * 4 + i][j] == '4')
                flagList[4]++;
            else if (map[(index / 4) * 4 + i][j] == '5')
                flagList[5]++;
            else if (map[(index / 4) * 4 + i][j] == '6')
                flagList[6]++;
            else if (map[(index / 4) * 4 + i][j] == '7')
                flagList[7]++;
            else if (map[(index / 4) * 4 + i][j] == '8')
                flagList[8]++;
            else if (map[(index / 4) * 4 + i][j] == '9')
                flagList[9]++;
            else if (map[(index / 4) * 4 + i][j] == 'A')
                flagList[10]++;
            else if (map[(index / 4) * 4 + i][j] == 'B')
                flagList[11]++;
            else if (map[(index / 4) * 4 + i][j] == 'C')
                flagList[12]++;
            else if (map[(index / 4) * 4 + i][j] == 'D')
                flagList[13]++;
            else if (map[(index / 4) * 4 + i][j] == 'E')
                flagList[14]++;
            else if (map[(index / 4) * 4 + i][j] == 'F')
                flagList[15]++;
        }
        for (int j = 0; j < 16; j++)
            if (flagList[j] > 1) {
                ans = false;
                return ans;
            }
    }
    return ans;
}

bool isLegalRow(int index) {
    bool ans = true;
    int flagList[16] = {0};
    for (int i = 0; i < 4; i++) {
        memset(flagList, 0, 16 * sizeof(flagList[0]));
        for (int j = 0; j < (index / 4 + 1) * 4; j++) {
            if (map[index / 4 + i][j] == '0')
                flagList[0]++;
            else if (map[j][(index % 4) * 4 + i] == '1')
                flagList[1]++;
            else if (map[j][(index % 4) * 4 + i] == '2')
                flagList[2]++;
            else if (map[j][(index % 4) * 4 + i] == '3')
                flagList[3]++;
            else if (map[j][(index % 4) * 4 + i] == '4')
                flagList[4]++;
            else if (map[j][(index % 4) * 4 + i] == '5')
                flagList[5]++;
            else if (map[j][(index % 4) * 4 + i] == '6')
                flagList[6]++;
            else if (map[j][(index % 4) * 4 + i] == '7')
                flagList[7]++;
            else if (map[j][(index % 4) * 4 + i] == '8')
                flagList[8]++;
            else if (map[j][(index % 4) * 4 + i] == '9')
                flagList[9]++;
            else if (map[j][(index % 4) * 4 + i] == 'A')
                flagList[10]++;
            else if (map[j][(index % 4) * 4 + i] == 'B')
                flagList[11]++;
            else if (map[j][(index % 4) * 4 + i] == 'C')
                flagList[12]++;
            else if (map[j][(index % 4) * 4 + i] == 'D')
                flagList[13]++;
            else if (map[j][(index % 4) * 4 + i] == 'E')
                flagList[14]++;
            else if (map[j][(index % 4) * 4 + i] == 'F')
                flagList[15]++;
        }
        for (int j = 0; j < 16; j++)
            if (flagList[j] > 1) {
                ans = false;
                return ans;
            }
    }
    return ans;
}

void dfs(int index, int *tmp) {
    int ciShu = 0;
    for (int i = 0; i < 4; i++) {
        if (isLegal(index)) {
            ciShu = i;
            if (index % 4 == 3) {
                tmp[3] = ciShu;
                int sum = tmp[0] + tmp[1] + tmp[2] + tmp[3];
                if (solution[index / 4][0] == 1) {
                    if (solution[index / 4][1] > sum) {
                        solution[index / 4][1] = sum;
                        solution[index / 4][2] = tmp[0];
                        solution[index / 4][3] = tmp[1];
                        solution[index / 4][4] = tmp[2];
                        solution[index / 4][5] = tmp[3];
                        for (int j = 0; j < ciShu; j++)
                            reRot(index);
                        return;
                    }
                } else {
                    solution[index / 4][0] = 1;
                    solution[index / 4][1] = sum;
                    solution[index / 4][2] = tmp[0];
                    solution[index / 4][3] = tmp[1];
                    solution[index / 4][4] = tmp[2];
                    solution[index / 4][5] = tmp[3];
                    for (int j = 0; j < ciShu; j++)
                        reRot(index);
                    return;
                }
            } else {
                tmp[index % 4] = ciShu;
                dfs(index + 1, tmp);
            }
        }
        rot(index);
    }
    return;
}

void dfsRow(int index, int *tmp) {
    if (index != 12) {
        if (isLegalRow(index)) {
            tmp[index / 4] = 1;
            dfsRow(index + 4, tmp);
        } else {
            rot(index);
            rot(index);
            tmp[index / 4] = 2;
            dfs(index + 4, tmp);
        }
    } else {
        if (isLegalRow(index)) {
            tmp[index / 4] = 1;
            solution[4][0] = tmp[0];
            solution[4][1] = tmp[1];
            solution[4][2] = tmp[2];
            solution[4][3] = tmp[3];
        } else {
            rot(index);
            rot(index);
            tmp[index / 4] = 2;
            solution[4][0] = tmp[0];
            solution[4][1] = tmp[1];
            solution[4][2] = tmp[2];
            solution[4][3] = tmp[3];
        }
    }
    return;
}

int main() {
    int zuShu = 0;
    scanf("%d", &zuShu);
    while (zuShu--) {
        memset(map, '\0', 17 * 17 * sizeof(char));
        memset(solution, -1, 6 * 7 * sizeof(int));
        int tmp[5] = {0};
        for (int i = 0; i < 16; i++)
            scanf("%s", map[i]);
        dfs(0, tmp);
        for (int i = 2; i < 6; i++)
            for (int j = 0; j < solution[0][i]; j++)
                rot(i - 2);
        dfs(4, tmp);
        for (int i = 2; i < 6; i++)
            for (int j = 0; j < solution[1][i]; j++)
                rot(4 + i - 2);
        dfs(8, tmp);
        for (int i = 2; i < 6; i++)
            for (int j = 0; j < solution[2][i]; j++)
                rot(8 + i - 2);
        dfs(12, tmp);
        for (int i = 2; i < 6; i++)
            for (int j = 0; j < solution[3][i]; j++)
                rot(12 + i - 2);
        dfsRow(0, tmp);
        int sum1 = 0, sum2 = 0;
        for (int i = 0; i < 4; i++) {
            if (solution[4][i] == 1)
                for (int j = 0; j < 4; j++) {
                    sum1 += solution[i][2 + j];
                    sum2 += (solution[i][2 + j] + 2) % 4;
                }
            else
                for (int j = 0; j < 4; j++) {
                    sum2 += solution[i][2 + j];
                    sum1 += (solution[i][2 + j] + 2) % 4;
                }
        }
        if (sum1 < sum2) {
            printf("%d\n", sum1);
            for (int i = 0; i < 16; i++)
                for (int j = 0; j < solution[i / 4][i % 4 + 2]; j++)
                    printf("%d %d\n", i / 4 + 1, i % 4 + 1);
        } else {
            printf("%d\n", sum2);
            for (int i = 0; i < 16; i++)
                for (int j = 0; j < (solution[i / 4][i % 4 + 2] + 2) % 4; j++)
                    printf("%d %d\n", i / 4 + 1, i % 4 + 1);
        }
    }
    return 0;
}