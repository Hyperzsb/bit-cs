#include <algorithm>
#include <cstdio>
#include <cstring>

struct point {
    char name;
    int neighbor_num;
    char neighbor[500];
};

bool comp(point a, point b) {
    return a.name < b.name;
}

int main() {
    point point_list[100];
    char str[500] = {'\0'};
    int point_num = 0;
    while (gets(str) != NULL) {
        int length = strlen(str);
        int index = -1;
        for (int i = 0; i < point_num; i++)
            if (str[0] == point_list[i].name) {
                index = i;
                break;
            }
        if (index != -1) {
            for (int i = 1; i < length; i++) {
                if (str[i] == ' ')
                    continue;
                else
                    point_list[index].neighbor[point_list[index].neighbor_num++] = str[i];
            }
        } else {
            point_list[point_num].name = str[0];
            point_list[point_num].neighbor_num = 0;
            for (int i = 1; i < length; i++) {
                if (str[i] == ' ')
                    continue;
                else
                    point_list[point_num].neighbor[point_list[point_num].neighbor_num++] = str[i];
            }
            point_num++;
        }
    }

    std::sort(point_list, point_list + point_num, comp);

    for (int i = 0; i < point_num; i++) {
        for (int j = 0; j < point_num - 1; j++) {
            int sum = 0;
            for (int k = 0; k < point_list[i].neighbor_num; k++)
                if (point_list[j].name == point_list[i].neighbor[k])
                    sum += 1;
            printf("%d ", sum);
        }
        int sum = 0;
        for (int k = 0; k < point_list[i].neighbor_num; k++)
            if (point_list[point_num - 1].name == point_list[i].neighbor[k])
                sum += 1;
        printf("%d\n", sum);
    }

    return 0;
}