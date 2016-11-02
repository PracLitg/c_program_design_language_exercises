#include "iolines.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
