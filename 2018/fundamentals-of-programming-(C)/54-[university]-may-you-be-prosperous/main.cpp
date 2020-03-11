#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main() {
    int renShu = 0;
    scanf("%d", &renShu);
    char **peolist = (char **) malloc(renShu * sizeof(char *));
    int **money = (int **) malloc(renShu * sizeof(int *));
    for (int i = 0; i < renShu; i++) {
        peolist[i] = (char *) malloc(15 * sizeof(char));
        money[i] = (int *) malloc(2 * sizeof(int));
        for (int j = 0; j < 2; j++)
            money[i][j] = 0;
        scanf("%s", peolist[i]);
    }
    char name[15] = {'\0'};
    int mon = 0, ren = 0;
    for (int i = 0; i < renShu; i++) {
        scanf("%s", name);
        scanf("%d%d", &mon, &ren);
        if (mon == 0 || ren == 0)
            continue;
        for (int j = 0; j < renShu; j++)
            if (strcmp(peolist[j], name) == 0) {
                money[j][0] = mon - mon % ren;
                //printf("------------\n%d %d\n------------\n",j,money[j][0]);
                break;
            }
        for (int j = 0; j < ren; j++) {
            scanf("%s", name);
            for (int k = 0; k < renShu; k++)
                if (strcmp(peolist[k], name) == 0) {
                    money[k][1] += mon / ren;
                    //printf("%d %d %d\n",k,money[k][0],money[k][1]);
                    break;
                }
        }
    }
    for (int i = 0; i < renShu; i++) {
        printf("%s ", peolist[i]);
        printf("%d\n", money[i][1] - money[i][0]);
    }

    return 0;
}