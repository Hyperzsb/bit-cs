#include<stdio.h>
#include<string.h>
#include<malloc.h>

int main() {
    int zuShu = 0, ans = 0, flag = 0;
    scanf("%d", &zuShu);
    char **strList = (char **) malloc(zuShu * sizeof(char *));
    int *flagList = (int *) malloc(zuShu * sizeof(int));
    int *lengthList = (int *) malloc(zuShu * sizeof(int));
    int i = 0;
    for (; i < zuShu; i++) {
        flagList[i] = 0;
        lengthList[i] = 0;
        strList[i] = (char *) malloc(25 * sizeof(char));
        scanf("%s", strList[i]);
        lengthList[i] = strlen(strList[i]);
        if (lengthList[i] <= 10) {
            flagList[i] = 1;
            continue;
        }
        int j = 0;
        for (; j < i; j++)
            if (flagList[j] == 0 && lengthList[j] == lengthList[i] && strcmp(strList[j], strList[i]) == 0) {
                flagList[i] = 1;
                flag = 1;
                break;
            }
        if (flag)
            flag = 0;
        else
            ans++;
    }
    printf("%d\n", ans);
    return 0;
}