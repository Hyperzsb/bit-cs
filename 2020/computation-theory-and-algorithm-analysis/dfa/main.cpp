#include <cstdio>
#include <cstring>

bool IsLegal(const char *str) {
    int length = strlen(str), start = 0, end = length - 1, mid = -1;
    for (int i = 0; i < length; i++)
        if (str[i] == ' ')
            start = i + 1;
        else
            break;
    for (int i = length - 1; i >= 0; i--)
        if (str[i] == ' ')
            end = i - 1;
        else
            break;

    if (start == length) {
//        printf("1\n");
        return false;
    }

    for (int i = start; i <= end; i++)
        if (str[i] == ' ') {
//            printf("2\n");
            return false;
        }

    for (int i = start; i <= end; i++)
        if (str[i] == 'e' || str[i] == 'E')
            mid = i;

    if (mid != -1) {
        bool has_point = false;
        for (int i = start; i < mid; i++)
            if (str[i] < '0' || str[i] > '9') {
                if (str[i] == '.') {
                    if (!has_point) {
                        if (i != start && i != mid - 1) {
                            has_point = true;
                        } else {
//                            printf("3\n");
                            return false;
                        }
                    } else {
//                        printf("4\n");
                        return false;
                    }
                } else if (str[i] == '+' || str[i] == '-') {
                    if (i != start) {
//                        printf("5\n");
                        return false;
                    }
                } else {
//                    printf("6\n");
                    return false;
                }
            }

        if (mid == end) {
//            printf("7\n");
            return false;
        }
        for (int i = mid + 1; i <= end; i++)
            if (str[i] < '0' || str[i] > '9') {
                if (str[i] == '+' || str[i] == '-') {
                    if (i != mid + 1) {
//                        printf("8\n");
                        return false;
                    }
                } else {
//                    printf("9\n");
                    return false;
                }
            }
        return true;
    } else {
        bool has_point = false;
        for (int i = start; i <= end; i++)
            if (str[i] < '0' || str[i] > '9') {
                if (str[i] == '.') {
                    if (!has_point) {
                        if (i != start && i != end) {
                            has_point = true;
                        } else {
//                            printf("10\n");
                            return false;
                        }
                    } else {
//                        printf("11\n");
                        return false;
                    }
                } else if (str[i] == '+' || str[i] == '-') {
                    if (i != start) {
//                        printf("12\n");
                        return false;
                    }
                } else {
//                    printf("13\n");
                    return false;
                }
            }
        return true;
    }
}

int main() {
    int zu_shu = 0;
    char str[2000] = {'\0'};
    scanf("%d", &zu_shu);
    getchar();
    while (zu_shu--) {
        gets(str);
        if (IsLegal(str))
            printf("LEGAL\n");
        else
            printf("ILLEGAL\n");
    }
    return 0;
}