#include<stdio.h>
#include<string.h>
#include<algorithm>

int getNum(char ch) {
    if (ch >= '0' && ch <= '9')
        return ch - '0';
    else if (ch == 'A' || ch == 'B' || ch == 'C')
        return 2;
    else if (ch == 'D' || ch == 'E' || ch == 'F')
        return 3;
    else if (ch == 'G' || ch == 'H' || ch == 'I')
        return 4;
    else if (ch == 'J' || ch == 'K' || ch == 'L')
        return 5;
    else if (ch == 'M' || ch == 'N' || ch == 'O')
        return 6;
    else if (ch == 'P' || ch == 'R' || ch == 'S')
        return 7;
    else if (ch == 'T' || ch == 'U' || ch == 'V')
        return 8;
    else if (ch == 'W' || ch == 'X' || ch == 'Y')
        return 9;
}

int getWei(int mod) {
    switch (mod) {
        case 1:
            return 128;
        case 2:
            return 64;
        case 3:
            return 32;
        case 4:
            return 16;
        case 5:
            return 8;
        case 6:
            return 4;
        case 7:
            return 2;
    }
}

struct node {
    int num;
    int ciShu;
} duplicationList[1505];

bool cmp(node a, node b) {
    return a.num < b.num;
}

int main() {
    int length = 0, flag = 1, index = 0, tmpNum = 0, isError = 0, errorNum = 0, tmpIndex = 0, mod = 0, tmpRes = 0, duplicationNum = 0;
    char numList[250000] = {0}, tmpStr[25] = {'\0'};
    while (~scanf("%s", tmpStr)) {
        length = strlen(tmpStr);
        for (int i = 0; i < length; i++) {
            if (tmpStr[i] == '-')
                continue;
            else if ((tmpStr[i] == 'Q' || tmpStr[i] == 'Z') ||
                     (index == 0 && tmpStr[i] != '3' && tmpStr[i] != '6' && tmpStr[i] != 'D' && tmpStr[i] != 'E' &&
                      tmpStr[i] != 'F' && tmpStr[i] != 'M' && tmpStr[i] != 'N' && tmpStr[i] != 'O'))
                if (errorNum == 0) {
                    printf("Error:\n%s\n", tmpStr);
                    isError = 1;
                    break;
                } else {
                    printf("%s\n", tmpStr);
                    isError = 1;
                    break;
                }
            else {
                tmpNum = tmpNum * 10 + getNum(tmpStr[i]);
                index++;
            }
        }
        if (isError) {
            isError = 0;
            tmpNum = 0;
            index = 0;
            errorNum++;
            continue;
        } else {
            tmpIndex = (tmpNum % 1000000) / 8;
            mod = (tmpNum % 1000000) % 8;
            if (tmpNum / 1000000 == 6)
                tmpIndex += 125000;
            if (mod == 0) {
                tmpRes = numList[tmpIndex - 1] & 1;
                if (tmpRes == 0)
                    numList[tmpIndex - 1] |= 1;
                else {
                    flag = 1;
                    for (int i = 0; i < duplicationNum; i++)
                        if (duplicationList[i].num == tmpNum) {
                            duplicationList[i].ciShu++;
                            flag = 0;
                            break;
                        }
                    if (flag) {
                        duplicationList[duplicationNum].num = tmpNum;
                        duplicationList[duplicationNum].ciShu = 2;
                        duplicationNum++;
                    }
                }
            } else {
                tmpRes = numList[tmpIndex] & getWei(mod);
                if (tmpRes == 0) {
                    numList[tmpIndex] |= getWei(mod);
                } else {
                    flag = 1;
                    for (int i = 0; i < duplicationNum; i++)
                        if (duplicationList[i].num == tmpNum) {
                            duplicationList[i].ciShu++;
                            flag = 0;
                            break;
                        }
                    if (flag) {
                        duplicationList[duplicationNum].num = tmpNum;
                        duplicationList[duplicationNum].ciShu = 2;
                        duplicationNum++;
                    }
                }
            }
            tmpNum = 0;
            index = 0;
        }
    }
    std::sort(duplicationList, duplicationList + duplicationNum, cmp);
    if (errorNum == 0)
        printf("Error:\nNot found.\n");
    printf("\nDuplication:\n");
    for (int i = 0; i < duplicationNum; i++)
        printf("%d-%04d %d\n", duplicationList[i].num / 10000, duplicationList[i].num % 10000,
               duplicationList[i].ciShu);
    if (duplicationNum == 0)
        printf("Not found.\n");
    return 0;
}