#include <cstdio>

int main() {
    int ans_list[100] = {0};
    ans_list[0] = 1, ans_list[2] = 3;
    for (int i = 4; i < 100; i += 2)
        ans_list[i] = 4 * ans_list[i - 2] - ans_list[i - 4];
    int index = 0;
    scanf("%d", &index);
    while (index != -1) {
        printf("%d\n", ans_list[index]);
        scanf("%d", &index);
    }
    return 0;
}