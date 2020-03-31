#include<stdio.h>
#include<malloc.h>
#include<algorithm>

using namespace std;
struct package {
    int id;
    int v;
    int previous;
    int next;
    int num;
};

bool cmp(package a, package b) {
    return a.v < b.v;
}

int main() {
    int geShu = 0;
    scanf("%d", &geShu);
    package *packList = (package *) malloc((geShu + 5) * sizeof(package));
    int *ansList = (int *) malloc((geShu + 5) * sizeof(int));
    packList[0].id = 0;
    packList[0].previous = 0;
    packList[0].next = 0;
    packList[0].num = 0;
    for (int i = 1; i < geShu + 1; i++) {
        scanf("%d", &packList[i].v);
        packList[i].id = i;
        packList[i].previous = 0;
        packList[i].next = 0;
        packList[i].num = 0;
    }
    std::sort(packList, packList + geShu, cmp);
    int index = 2;
    for (int i = 1; i < geShu + 1; i++)
        for (int j = index; j < geShu + 1; j++)
            if (packList[j].v >= packList[i].v * 2) {
                packList[j].previous = i;
                packList[i].next = j;
                packList[j].num += 1 + packList[i].num;
                index = j + 1;
                break;
            }
    int tmp = 0, ans = 0, flag = 0;
    for (int i = geShu; i >= 1; i--) {
        if (tmp == geShu)
            break;
        if (packList[i].next == 0) {
            tmp += packList[i].num + 1;
            ans++;
        }
    }
    printf("%d\n", ans);
    for (int i = 1; i < geShu + 1; i++) {
        if (flag == ans)
            break;
        if (packList[i].previous == 0) {
            int length = 0;
            tmp = i;
            while (packList[tmp].next != 0) {
                ansList[length] = packList[tmp].id;
                length++;
                tmp = packList[tmp].next;
            }
            ansList[length] = packList[tmp].id;
            length++;
            printf("%d", length);
            for (int j = 0; j < length; j++)
                printf(" %d", ansList[j]);
            printf("\n");
            flag++;
        }
    }
    return 0;
}