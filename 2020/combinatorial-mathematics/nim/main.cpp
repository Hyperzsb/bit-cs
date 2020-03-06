#include <stdio.h>
#include <stdlib.h>

int main() {
    int pile_num = 0;
    scanf("%d", &pile_num);
    while (pile_num != 0) {
        int *pile_list = (int *) malloc(pile_num * sizeof(int)), tmp = 0;
        for (int i = 0; i < pile_num; i++) {
            scanf("%d", &pile_list[i]);
            tmp ^= pile_list[i];
        }
        if (tmp == 0) {
            printf("0\n");
        } else {
            int sum = 0;
            for (int i = 0; i < pile_num; i++)
                if ((pile_list[i] ^ tmp) < pile_list[i])
                    sum++;
            printf("%d\n", sum);
        }
        scanf("%d", &pile_num);
    }
    return 0;
}