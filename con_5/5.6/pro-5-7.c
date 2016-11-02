#include <stdio.h>

#define MAXLINES 5000
#define MAXLEN 1000

char* lineptr[MAXLINES];
int myReadlines(char* lineptr[], int nlines, char all_lines[][MAXLEN]);
void writelines(char* lineptr[], int nlines);

int main() {
    char all_lines[MAXLINES][MAXLEN];


    int nlines;
    if ((nlines = myReadlines(lineptr, MAXLINES, all_lines)) >= 0) {
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("Error: Input too big to sort\n");
        return 1;
    }
}

int myGetline(char s[], int lim) {
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    if (c == '\n')
        s[i++] = '\n';
    s[i] = '\0';
    return i;
}

int myReadlines(char* lineptr[], int maxlines, char all_lines[][MAXLEN]) {
    int len, nlines;
    char line[MAXLEN];

    nlines = 0;
    while ((len = myGetline(all_lines[nlines], MAXLEN)) > 0) {
        if (nlines >= maxlines) {
            return -1;
        } else {
            all_lines[nlines][len - 1] = '\0';
            lineptr[nlines] = all_lines[nlines];
            //printf("%s\n", lineptr[nlines]);
            nlines++;
        }
    }

    return nlines;
}

void writelines(char* lineptr[], int nlines) {
    int i;

    for (i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}
