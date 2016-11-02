#include <stdio.h>
#include <stdlib.h>

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

void itob(int n, char s[], int b) {
    int sign = 0;
    if (n < 0)
        sign = 1;

    int i = 0;
    while (n != 0) {
        int tmp = abs(n % b);
        int c;
        switch (tmp) {
            case 10:
                c = 'A';
                break;
            case 11:
                c = 'B';
                break;
            case 12:
                c = 'C';
                break;
            case 13:
                c = 'D';
                break;
            case 14:
                c = 'E';
                break;
            case 15:
                c = 'D';
                break;
            default:
                c = tmp + '0';
                break;
        }
        s[i++] = c;
        n /= b;
    }
    if (sign)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s, i);
}

int main() {
    int n, s;
    char str[MAXLINE];
    scanf("%d%d", &n, &s);
    itob(n, str, s);
    printf("%s\n", str);
}
