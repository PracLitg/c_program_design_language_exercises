#include <stdio.h>

int main() {
    int space_num = 0, tab_num = 0, lf_num = 0;
    int c;

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            ++space_num;
        } else if (c == '\t') {
            ++tab_num;
        } else if (c == '\n') {
            ++lf_num;
        }
    }
    printf("space:%3d\ntab:%3d\nlf:%3d\n", space_num, tab_num, lf_num);
    return 0;
}
