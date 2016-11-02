#include <stdio.h>

// type int has 32 bits
#define INT_LEN 32

int setbits(unsigned int fir, int st, int len, int sec) {
    // get new_sec starts at st
    unsigned int new_sec = sec & (~0 >> st);

    // get a number that starts at st and its length is len
    int ri = INT_LEN - st - len + 1;
    int tmp = ~0 >> ri << ri << st >> st;

    unsigned int new_fir = fir | tmp;
    return new_fir & new_sec;
}

int main(int argc, char const *argv[]) {
    /* code */
    int fir, sec;
    scanf("%d%d", &fir, &sec);
    int res = setbits(fir, 29, 4, sec);
    printf("%d\n", res);
    return 0;
}
