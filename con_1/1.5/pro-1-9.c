#include <stdio.h>

int main() {
    int c;
    int space_exist = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            if (space_exist == 0) {
                space_exist = 1;
                putchar(c);
            }
        } else {
            putchar(c);
            space_exist = 0;
        }
    }
    return 0;
}

