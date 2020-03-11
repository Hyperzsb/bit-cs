#include<stdio.h>
#include<string.h>

int main() {
    char str[100] = {'\0'};
    gets(str);
    int len = strlen(str);
    if (str[0] == '\n') {
        printf("Yes\n");
        return 0;
    }
    for (int i = 0; i < len / 2; i++)
        if (str[i] != str[len - 1 - i]) {
            printf("No\n");
            return 0;
        }
    printf("Yes\n");
    return 0;
}