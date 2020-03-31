#include<stdio.h>
#include<algorithm>

#define INF 0x3f3f3f

bool cmp(int a, int b) {
    return a > b;
}

int main() {
    int area[2] = {0},
            suSheShu = 0, diDianShu = 0, tmpX = 0, tmpY = 0,
            max1 = -2100000000, max2 = -2100000000, max3 = -2100000000, max4 = -2100000000,
            ans = 2100000000, lengthList[4] = {0};
    scanf("%d%d%d", &area[0], &area[1], &suSheShu);
    for (int i = 0; i < suSheShu; i++) {
        scanf("%d%d", &tmpX, &tmpY);
        if (max1 < -tmpX - tmpY)
            max1 = -tmpX - tmpY;
        if (max2 < -tmpX + tmpY)
            max2 = -tmpX + tmpY;
        if (max3 < tmpX - tmpY)
            max3 = tmpX - tmpY;
        if (max4 < tmpX + tmpY)
            max4 = tmpX + tmpY;
    }
    scanf("%d", &diDianShu);
    for (int i = 0; i < diDianShu; i++) {
        scanf("%d%d", &tmpX, &tmpY);
        lengthList[0] = tmpX + tmpY + max1;
        lengthList[1] = tmpX - tmpY + max2;
        lengthList[2] = -tmpX + tmpY + max3;
        lengthList[3] = -tmpX - tmpY + max4;
        std::sort(lengthList, lengthList + 4, cmp);
        if (lengthList[0] < ans)
            ans = lengthList[0];
    }
    printf("%d\n", ans);

    return 0;
}