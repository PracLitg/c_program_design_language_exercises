#include <stdio.h>
#include <ctype.h>

#define MAXLINE 100

void myGetline(char s[], int lim) {
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
        s[i] = c;
    }
    /*if (c == '\n') {
        s[i] = c;
        i++;
    }*/
    s[i] = '\0';
}

void expand(char s[], char t[]) {
    // rm space and '-'
    int i;
    for (i = 0; isspace(s[i]); i++)
        ;
    for (; s[i] == '-'; i++)
        ;

    int j;
    for (j = 0; s[i] != '\0'; i++, j++) {
        if (s[i] != '-') {
            t[j] = s[i];
        } else {
            int f_c, a_c;
            f_c = s[i - 1];
            a_c = s[i + 1];
            if ('a' <= f_c && f_c <= 'z' && 'a' <= a_c && a_c <= 'z') {
                int k;
                for (k = f_c + 1; k < a_c; k++)
                    t[j++] = k;
                t[j] = a_c;
            } else {
                t[j] = s[i];
            }
        }
    }
    t[j] = '\0';
}

int main(int argc, char const *argv[]) {
    char s[MAXLINE];
    myGetline(s, MAXLINE);
    char t[MAXLINE];
    expand(s, t);
    printf("%s\n", t);
    return 0;
}
