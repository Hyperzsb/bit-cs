#include <cstdio>

int main() {
    int dimensional = 0;
    scanf("%d", &dimensional);
    int point_num = 1;
    for (int i = 0; i < dimensional; i++)
        point_num *= 2;
    int *point_order = new int[point_num];
    for (int i = 0; i < point_num; i++)
        scanf("%d", &point_order[i]);

    int *neighbor = new int[point_num];
    for (int i = 0; i < point_num; i++) {
        int index = 1;
        for (int j = 0; j < point_num; j++)
            neighbor[j] = 0;
        for (int j = 0; j < dimensional; j++) {
            neighbor[point_order[i] ^ index] = 1;
            index *= 2;
        }
        for (int j = 0; j < point_num - 1; j++)
            printf("%d ", neighbor[point_order[j]]);
        printf("%d\n", neighbor[point_order[point_num - 1]]);
    }

    delete[]point_order;
    delete[]neighbor;

    return 0;
}