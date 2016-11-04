#include "iolines.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINE 1000
#define MAXLEN 1000
#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;


int getch() {
    return (bufp > 0) ? buf[--bufp] : getchar();
}


void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("Ungetch: Too many characters\n");
    else
        buf[bufp++] = c;
}


/*
 * 功能: 从输入中读取下一个单词或字符,具有下划线处理,识别注释等功能
 * return type: 单词首字符
 */
int getword(char* word, int lim) {
    int c;
    char* w = word;

    while (isspace(c = getch()))
        ;

    if (c != EOF) {
        *w++ = c;
    }
    if (isalpha(c) || c == '#' || c == '_') {
        for (; --lim > 0; w++) {
            if (!isalnum(*w = getch()) || *w == '_') {
                ungetch(*w);
                break;
            }
        }
    } else if (c == '\'') {
        while (--lim > 0) {
            if ((*w++ = getch()) == '\'') {
                break;
            }
            if (*w == EOF) {
                ungetch(*w);
                break;
            }
        }
    } else if (c == '\"') {
        while (--lim > 0) {
            if ((*w++ = getch()) == '\"') {
                break;
            }
            if (*w == EOF) {
                ungetch(*w);
                break;
            }
        }
    } else if (c == '/') {
        int d;
        if ((d = getch()) == '*') {
            while ((d = getch()) != EOF) {
                if (d == '*') {
                    int t;
                    if ((t = getch()) == '/') {
                        break;
                    } else {
                        ungetch(t);
                    }
                }
            }
        } else {
            ungetch(d);
        }
    }

    *w = '\0';
    return c;
}


int readlines(char* lineptr[], int maxlines) {
    int len, nlines;
    char* p;
    char line[MAXLEN];
    nlines = 0;

    char* s = NULL;
    while (s = fgets(line, MAXLEN, stdin)) {
        len = strlen(s);
        p = (char*)malloc(sizeof(p) * (len + 1));
        if (nlines >= maxlines || !p)
            return -1;
        else {
            line[len] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

void writelines(char* lineptr[], int nlines) {
    int i;

    for (i = 0; i < nlines; i++) {
        printf("%s", lineptr[i]);
    }
}

void freeReadMemory(char* lineptr[], int nlines) {
    int i;
    for (int i = 0; i < nlines; i++)
        free(lineptr[i]);
}
