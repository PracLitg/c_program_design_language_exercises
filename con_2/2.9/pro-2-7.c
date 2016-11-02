#include <stdio.h>

#define INT_LEN 32

/* the first bit of ori is considered as 1 but not 0 */
int invert(int ori, int st, int len) {
    if (st + len - 1 > INT_LEN) {
        printf("Wrong Length\n");
        return -1;
    } else {
        unsigned int tmp = ~0;
        if (st > 0)
            tmp = tmp << (st - 1) >> (st - 1);
        int sz = INT_LEN - st - len + 1;
        tmp = tmp >> sz << sz;

        int new_num1 = ori & tmp;
        int new_num2 = ori | tmp;
        return new_num2 & (~new_num1);
    }
}

int main(int argc, char const *argv[]) {
    /* code */
    int ori;
    ori = 0x00ff0000;
    int res = invert(ori, 1, 4);
    printf("%x\n", res);
}
