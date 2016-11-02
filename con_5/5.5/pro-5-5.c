#include <stdio.h>

void myStrncpy(char* s, char* t, int num) {
    int i = 0;
    while ((*s = *t) && (i < num)) {
        s++;
        t++;
        i++;
    }
    while (i <= num) {
        *s++ = '\0';
        i++;
    }
}

void myStrncat(char* s, char* t, int num) {
    while (*s)
        s++;

    int i;
    for (i = 0; i < num && *(t + i); i++) {
        *(s + i) = *(t + i);
    }
    while (i < num) {
        *(s + i) = '\0';
        i++;
    }
}

int myStrncmp(char* s, char* t, int num) {
    int i;

    for (i = 0; i < num; i++) {
        if (*(s + i) == '\0' || *(t + i) == '\0')
            return 0;
        if (*(s + i) != *(t + i))
            return *(s + i) - *(t + i) > 0 ? 1 : -1;
    }
    return 0;
}

int main() {
    char s[30] = "helloworld";
    char t[20] = "litong";
    char t1[20] = "hala";

    myStrncpy(s, t, 5);
    printf("%s\n", s);
    myStrncpy(s, t, 10);
    printf("%s\n", s);

    myStrncat(s, t1, 3);
    printf("%s\n", s);
    myStrncat(s, t1, 6);
    printf("%s\n", s);

    printf("%d\n", myStrncmp(s, t, 3));
    printf("%d\n", myStrncmp(s, t1, 3));
}
