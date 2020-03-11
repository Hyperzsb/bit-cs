#include<stdio.h>

int main() {
    int a, b, c, i = 1, d, e, t;
    scanf("%d%d%d", &a, &b, &c);
    if (a % 400 == 0 || a % 4 == 0 && a % 100 != 0) {
        switch (b) {
            case 1:
                d = 0;
                break;
            case 2:
                d = 31;
                break;
            case 3:
                d = 60;
                break;
            case 4:
                d = 91;
                break;
            case 5:
                d = 121;
                break;
            case 6:
                d = 152;
                break;
            case 7:
                d = 182;
                break;
            case 8:
                d = 213;
                break;
            case 9:
                d = 244;
                break;
            case 10:
                d = 274;
                break;
            case 11:
                d = 305;
                break;
            case 12:
                d = 335;
                break;
        }
        d = d + c + (a - 1901) * 365 + (a - 1900) / 4 - 1;
        e = d % 7;
        i = i + e;
    } else {
        switch (b) {
            case 1:
                d = 0;
                break;
            case 2:
                d = 31;
                break;
            case 3:
                d = 59;
                break;
            case 4:
                d = 90;
                break;
            case 5:
                d = 120;
                break;
            case 6:
                d = 151;
                break;
            case 7:
                d = 181;
                break;
            case 8:
                d = 212;
                break;
            case 9:
                d = 243;
                break;
            case 10:
                d = 273;
                break;
            case 11:
                d = 304;
                break;
            case 12:
                d = 334;
                break;
        }
        d = d + c + (a - 1901) * 365 + (a - 1900) / 4;
        e = d % 7;
        i = i + e;
    }
    t = (d - 40641) / 91 % 5;

    switch (t) {
        case 0:
            switch (i) {
                case 1:
                    printf("3 and 8.\n");
                    return 0;
                case 2:
                    printf("4 and 9.\n");
                    return 0;
                case 3:
                    printf("5 and 0.\n");
                    return 0;
                case 4:
                    printf("1 and 6.\n");
                    return 0;
                case 5:
                    printf("2 and 7.\n");
                    return 0;
                case 6:
                    printf("Free.\n");
                    return 0;
                case 7:
                    printf("Free.\n");
                    return 0;
            }
        case 1:
            switch (i) {
                case 1:
                    printf("2 and 7.\n");
                    return 0;
                case 2:
                    printf("3 and 8.\n");
                    return 0;
                case 3:
                    printf("4 and 9.\n");
                    return 0;
                case 4:
                    printf("5 and 0.\n");
                    return 0;
                case 5:
                    printf("1 and 6.\n");
                    return 0;
                case 6:
                    printf("Free.\n");
                    return 0;
                case 7:
                    printf("Free.\n");
                    return 0;
            }

        case 2:
            switch (i) {
                case 1:
                    printf("1 and 6.\n");
                    return 0;
                case 2:
                    printf("2 and 7.\n");
                    return 0;
                case 3:
                    printf("3 and 8.\n");
                    return 0;
                case 4:
                    printf("4 and 9.\n");
                    return 0;
                case 5:
                    printf("5 and 0.\n");
                    return 0;
                case 6:
                    printf("Free.\n");
                    return 0;
                case 7:
                    printf("Free.\n");
                    return 0;
            }
        case 3:
            switch (i) {
                case 1:
                    printf("5 and 0.\n");
                    return 0;
                case 2:
                    printf("1 and 6.\n");
                    return 0;
                case 3:
                    printf("2 and 7.\n");
                    return 0;
                case 4:
                    printf("3 and 8.\n");
                    return 0;
                case 5:
                    printf("4 and 9.\n");
                    return 0;
                case 6:
                    printf("Free.\n");
                    return 0;
                case 7:
                    printf("Free.\n");
                    return 0;
            }
        case 4:
            switch (i) {
                case 1:
                    printf("4 and 9.\n");
                    return 0;
                case 2:
                    printf("5 and 0.\n");
                    return 0;
                case 3:
                    printf("1 and 6.\n");
                    return 0;
                case 4:
                    printf("2 and 7.\n");
                    return 0;
                case 5:
                    printf("3 and 8.\n");
                    return 0;
                case 6:
                    printf("Free.\n");
                    return 0;
                case 7:
                    printf("Free.\n");
                    return 0;
            }
    }
    return 0;
}