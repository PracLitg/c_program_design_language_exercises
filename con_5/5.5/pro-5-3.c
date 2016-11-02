#include <stdio.h>

void myStrcat(char* s, char* t) {
    while (*s)
        s++;

    while (*s++ = *t++)
        ;
}

int main() {
    char s[20] = "hello";
    char t[] = "world";
    myStrcat(s, t);
    printf("%s\n%s\n", s, t);
    return 0;
}
