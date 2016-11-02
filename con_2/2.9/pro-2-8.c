#include <stdio.h>

#define INT_LEN 32

int rightrot(unsigned int ori, int len) {
    int std = 1;
    for (int i = 0; i < len; i++) {
        int last_bit = ori & std;
        int fir_bit = last_bit << (INT_LEN - 1);
        ori >>= 1;
        ori |= fir_bit;
    }
    return ori;
}

int main(int argc, char const *argv[]) {
    /* code */
    unsigned int ori = 0x0000f000;
    for (int i = 0; i < 16; i++) {
        printf("%x\n", rightrot(ori, i));
    }
    return 0;
}
