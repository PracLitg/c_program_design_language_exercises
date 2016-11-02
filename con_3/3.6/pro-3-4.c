#include <stdio.h>

#define MAXLINE 100

void reverse(char s[], int n) {
    int i, j;
    for (i = 0, j = n - 1; i < j; i++, j--) {
        int tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
    }
    s[n] = '\0';
}

void itoa(int n, char s[]) {
    int i = 0, sign = 0;

    while (n != 0) {
        int tmp = n % 10;
        if (tmp < 0) {
            s[i++] = -tmp + '0';
            sign = 1;
        } else {
            s[i++] = tmp + '0';
        }
        n = n / 10;
    }
    if (sign)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s, i);
}

int main() {
    char s[MAXLINE];
    int n;
    scanf("%x", &n);
    itoa(n, s);
    printf("%s\n", s);
    return 0;
}
