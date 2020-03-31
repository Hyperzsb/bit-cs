#include<stdio.h>
#include<stdlib.h>
#include<algorithm>

struct attack {
    int id;
    int time;
    int damage;
};

bool cmp1(attack a, attack b) {
    return a.time < b.time;
}

bool cmp2(attack a, attack b) {
    return a.damage > b.damage;
}

int main() {
    int renShu = 0, zuShu = 0, damageNum = 0, invalid = 0;
    scanf("%d%d", &renShu, &zuShu);
    attack *timeList = (attack *) malloc(renShu * sizeof(attack));
    int *invalidList = (int *) malloc(renShu * sizeof(int));
    for (int i = 0; i < renShu; i++) {
        scanf("%d%d", &timeList[i].time, &timeList[i].damage);
        damageNum += timeList[i].damage;
    }
    std::sort(timeList, timeList + renShu, cmp1);
    for (int i = 0; i < zuShu; i++) {
        scanf("%d", &invalid);
        int index = 0, flag = 1, max = timeList[0].damage, tmp = timeList[0].damage;
        for (int j = 1; j < renShu; j++)
            if (timeList[j].time - timeList[j - 1].time >= invalid)
                if (tmp > max) {
                    max = tmp;
                    tmp = timeList[j].damage;
                    index = j;
                    continue;
                } else {
                    tmp = timeList[j].damage;
                    index = j;
                    continue;
                }
            else {
                tmp += timeList[j].damage;
                for (; timeList[j].time - timeList[index].time >= invalid;) {
                    tmp -= timeList[index].damage;
                    index++;
                }
                if (tmp > max) {
                    max = tmp;
                    continue;
                } else {
                    continue;
                }
            }
        printf("%d\n", damageNum - max);
    }

    return 0;
}