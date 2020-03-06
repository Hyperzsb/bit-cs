#include <stdio.h>

int main() {
    int zu_shu = 0;
    scanf("%d", &zu_shu);
    while (zu_shu--) {
        int person_num = 0;
        scanf("%d", &person_num);
        if (person_num % 2 == 0)
            printf("%d\n", (person_num / 2) * (person_num / 2 - 1));
        else
            printf("%d\n", (person_num / 2) * (person_num / 2 - 1) / 2 + (person_num / 2 + 1) * (person_num / 2) / 2);
    }
    return 0;
}