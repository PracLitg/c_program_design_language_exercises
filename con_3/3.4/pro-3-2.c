#include <stdio.h>

#define MAXLINE 100

void escape(char s[], char t[], int lim) {
    int i;
    for (i = 0; i < lim - 1 && t[i] != '\0'; i++) {
        switch (t[i]) {
            case '\t':
                s[i++] = '\\';
                s[i] = 't';
                break;
            case '\n':
                s[i++] = '\\';
                s[i] = 'n';
                break;
            default:
                s[i] = t[i];
        }
    }
    s[i] = '\0';
 }

void myGetline(char s[], int lim) {
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
        s[i] = c;
    }
    if (c == '\n') {
        s[i] = c;
        i++;
    }
    s[i] = '\0';
}

int main() {
    int c;
    char s[MAXLINE];
    char t[MAXLINE];

    int len = 0;
    myGetline(t, MAXLINE);
    escape(s, t, MAXLINE);
    printf("%s\n", s);
    return 0;
}
