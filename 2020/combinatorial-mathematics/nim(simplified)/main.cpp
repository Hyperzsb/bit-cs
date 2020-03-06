#include <stdio.h>

int main() {
    int zu_shu = 0;
    scanf("%d", &zu_shu);
    while (zu_shu--) {
        int stick_num = 0;
        scanf("%d", &stick_num);
        if (stick_num % 3 == 0)
            printf("2\n");
        else if (stick_num % 3 == 1)
            printf("0\n");
        else
            printf("1\n");
    }
    return 0;
}