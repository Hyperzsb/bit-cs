#include<stdio.h>
#include<math.h>

int map[800][800] = {0};

int minNum(int a, int b, int c, int d) {
    int tmp = a < b ? a : b;
    tmp = tmp < c ? tmp : c;
    tmp = tmp < d ? tmp : d;
    return tmp;
}

int maxNum(int a, int b, int c, int d) {
    int tmp = a > b ? a : b;
    tmp = tmp > c ? tmp : c;
    tmp = tmp > d ? tmp : d;
    return tmp;
}

double dis(int x1, int y1, int x2, int y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int main() {
    int width = 0, height = 0, xc = 0, yc = 0, r = 0, x1 = 0, y1 = 0, x2 = 0, y2 = 0, x3 = 0, y3 = 0, x4 = 0, y4 = 0;
    scanf("%d%d", &width, &height);
    scanf("%d%d%d", &xc, &yc, &r);
    scanf("%d%d%d%d", &x1, &y1, &x3, &y3);
    for (int i = 0; i <= 2 * r; i++)
        for (int j = 0; j <= 2 * r; j++)
            if (dis(xc + r - i, yc + r - j, xc, yc) > r)
                map[xc + r - i + 400][yc + r - j + 400] = 0;
            else
                map[xc + r - i + 400][yc + r - j + 400] = 1;
    int a = ((x3 + y3) - (x1 + y1)) / 2, b = ((y3 - x3) - (y1 - x1)) / 2;
    x4 = x1 + a, y4 = y1 + b;
    x2 = x3 - a, y2 = y3 - b;
    int minx = minNum(x1, x2, x3, x4);
    int maxx = maxNum(x1, x2, x3, x4);
    int miny = minNum(y1, y2, y3, y4);
    int maxy = maxNum(y1, y2, y3, y4);
    for (int i = minx; i <= maxx; i++)
        for (int j = miny; j <= maxy; j++) {
            int x = x1 - b + i, y = y3 - a - b + j;
            if ((((x4 - x1) * (i - x1) + (y4 - y1) * (j - y1)) >= 0) &&
                (((x3 - x4) * (i - x4) + (y3 - y4) * (j - y4)) >= 0) &&
                (((x2 - x3) * (i - x3) + (y2 - y3) * (j - y3)) >= 0) &&
                (((x1 - x2) * (i - x2) + (y1 - y2) * (j - y2)) >= 0))
                map[i + 400][j + 400] += 1;
        }
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++)
            if (map[i + 400][j + 400] > 0)
                printf("/");
            else
                printf("\\");
        printf("\n");
    }
    return 0;
}