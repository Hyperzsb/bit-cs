#include "crc.h"

int BinaryToDecimal(const char *num, int h) {
    int ans = 0;
    for (int i = 0; i < h; i++) {
        ans *= 2;
        ans += num[i];
    }
    return ans;
}

char *DecimalToBinary(int num, int cnt) {
    char *s = (char *) malloc((cnt+2) * sizeof(char));
    char *s1 = (char *) malloc((cnt+2) * sizeof(char));
    for( int i = 0; i < cnt; i++ ){
        s[i] = 0;
        s1[i] = 0;
    }
    int cnt1 = 0;
    while (num) {
        s[cnt1] = num % 2;
        num /= 2;
        cnt1++;
    }
    for (int i = 0; i < cnt; i++) {
        s1[cnt-1-i] = s[i];
    }
    return s1;
}


int GetCRC(struct Frame *s, int flag) {
    char divisor_binary[17] = {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
    char* p = (char *) malloc( (8*MAX_DATA_LENGTH+20)*sizeof(char));
    for( int i = 0; i < MAX_DATA_LENGTH; i++ ){
        char *onechar;
        onechar = DecimalToBinary(s->data[i], 8);
        for( int j = 0; j < 8; j++ ){
            p[i*8+j] = onechar[j];
        }
        free(onechar);
    }
    int divisor = BinaryToDecimal(divisor_binary, 17);
    char* tmp = (char *) malloc( (8*MAX_DATA_LENGTH+16+20)*sizeof(char));
    for (int i = 0; i < MAX_DATA_LENGTH*8; i++) {
        tmp[i] = p[i];
    }
    if( flag == 0 ){
        for (int i = MAX_DATA_LENGTH*8; i < MAX_DATA_LENGTH*8 + 16; i++) {
            tmp[i] = 0;
        }
    }else{
        char *crc;
        crc = DecimalToBinary(s->checksum, 16);
        int cnt = 0;
        for (int i = MAX_DATA_LENGTH*8; i < MAX_DATA_LENGTH*8 + 16; i++) {
            tmp[i] = crc[cnt++];
        }
    }
    char dividend_binary[16];
    for (int i = 0; i < 16; i++) {
        dividend_binary[i] = tmp[i];
    }
    int dividend = BinaryToDecimal(dividend_binary, 16);
    for (int i = 16; i < MAX_DATA_LENGTH*8 + 16; i++) {
        dividend = dividend << 1;
        dividend ^= tmp[i];
        if ((dividend & 65536) != 0) {
            dividend = dividend ^ divisor;
        }
    }
    free(p);
    return dividend;
}

int CheckCRC(struct Frame *s) {
    return GetCRC(s, 1);
}