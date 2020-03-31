#include<stdio.h>
#include<malloc.h>
#include<algorithm>

struct ball {
    int id;
    int geometry[5];
};

bool cmp(int a, int b) {
    return a > b;
}

bool cmp1(ball a, ball b) {
    if (a.geometry[0] > b.geometry[0])
        return true;
    else if (a.geometry[0] == b.geometry[0])
        if (a.geometry[1] > b.geometry[1])
            return true;
        else if (a.geometry[1] == b.geometry[1])
            if (a.geometry[2] > b.geometry[2])
                return true;
            else
                return false;
        else
            return false;
    else
        return false;
}

int main() {
    int geShu = 0, testList[5] = {0}, ansList[5] = {0};
    scanf("%d", &geShu);
    ball *ballList = (ball *) malloc((geShu + 5) * sizeof(ball));
    for (int i = 0; i < geShu; i++) {
        scanf("%d%d%d", &testList[0], &testList[1], &testList[2]);
        std::sort(testList, testList + 3, cmp);
        ballList[i].geometry[0] = testList[0], ballList[i].geometry[1] = testList[1], ballList[i].geometry[2] = testList[2];
        ballList[i].id = i + 1;
    }
    std::sort(ballList, ballList + geShu, cmp1);
    for (int i = 0; i < geShu; i++) {
        if (ballList[i].geometry[0] <= ansList[0])
            break;
        if (ballList[i].geometry[0] == ballList[i + 1].geometry[0] &&
            ballList[i].geometry[1] == ballList[i + 1].geometry[1]) {
            ballList[i].geometry[2] += ballList[i + 1].geometry[2];
            std::sort(ballList[i].geometry, ballList[i].geometry + 3, cmp);
            if (ballList[i].geometry[2] > ansList[0]) {
                ansList[0] = ballList[i].geometry[2];
                ansList[1] = 2;
                ansList[2] = ballList[i].id;
                ansList[3] = ballList[i + 1].id;
            }
        } else {
            if (ballList[i].geometry[2] > ansList[0]) {
                ansList[0] = ballList[i].geometry[2];
                ansList[1] = 1;
                ansList[2] = ballList[i].id;
            }
        }
    }

    if (ansList[1] == 1)
        printf("%d\n%d\n", ansList[1], ansList[2]);
    else
        printf("%d\n%d %d\n", ansList[1], ansList[2], ansList[3]);

    return 0;
}