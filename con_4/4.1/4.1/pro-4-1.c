#include <stdio.h>
#include <string.h>

#define MAXLINE 100

int myGetline(char line[], int max);
int strrindex(char source[], char searchfor[]);

char tar[6] = "hello";

int main() {
    char line[MAXLINE];

    while (myGetline(line, MAXLINE) > 0) {
        int res;
        if ((res = strrindex(line, tar)) >= 0) {
            printf("%d\n", res);
        }
    }

    return 0;
}

int myGetline(char s[], int lim) {
    int c, i;
    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

int strrindex(char s[], char t[]) {
    int i, j, k;
    int len_s = strlen(s);
    int len_ts = strlen(t);

    for (i = len_s - 1; i > -1; i--) {
        for (j = len_ts - 1, k = i; j > -1 && t[j] == s[k]; j--, k--)
            ;
        if (j == -1 && k >= -1)
            return i - len_ts + 1;
    }
    return -1;
}
