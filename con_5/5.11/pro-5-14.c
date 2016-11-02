/*
 * pro-5-14 to pro-5-17
 */

#include "../../libraries/iolines/iolines.h"
#include "../../libraries/qsort/qsort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINES 100
#define MAXLEN 100

#define NUMERIC 1
#define DECR 2
#define FOLD 4
#define DIREC 8

static int option = 0;

int numcmp(char*, char*);
int charcmp(char*, char*);


int main(int argc, char const *argv[]) {
    int c;
    while (--argc > 0 && (*++argv)[0] == '-')
        while (c = *++argv[0])
            switch (c) {
                case 'n':
                    option |= NUMERIC;
                    break;
                case 'r':
                    option |= DECR;
                    break;
                case 'f':
                    option |= FOLD;
                    break;
                case 'd':
                    option |= DIREC;
                    break;
                default:
                    printf("Sort: Illegal option %c\n", c);
                    argc = 1;
                    break;
            }

    if (argc)
        printf("Usage: Sort -nr\n");
    else {
        char* line[MAXLINES];
        int n;
        if ((n = readlines(line, MAXLINES)) >= 0) {
            if (option & NUMERIC)
                qsortStrings((void**)line, 0, n - 1, (int(*)(void*, void*))numcmp);
            else if (option & FOLD)
                qsortStrings((void**)line, 0, n - 1, (int(*)(void*, void*))charcmp);
            else
                qsortStrings((void**)line, 0, n - 1, (int(*)(void*, void*))strcmp);

            if (option & DECR)
                reverse((void**)line, 0, n - 1);

            writelines(line, n);
        }
        freeReadMemory(line, n);
    }
    return 0;
}


int numcmp(char* fir, char* sec) {
    double n1, n2;

    n1 = atof(fir);
    n2 = atof(sec);

    if (n1 > n2)
        return 1;
    else if (n1 < n2)
        return -1;
    else
        return 0;
}


int charcmp(char* fir, char* sec) {
    while (!isalnum(*fir) && *fir != ' ' && *fir != '\0') {
        fir++;
    }
    while (!isalnum(*sec) && *sec != ' ' && *sec != '\0') {
        sec++;
    }

    int dir = option & DIREC;
    while (tolower(*fir) == tolower(*sec)) {
        if (*fir == '\0')
            return 0;
        fir++;
        sec++;
        if (dir) {
            if (!isalnum(*fir) && *fir != ' ')
                fir++;
            if (!isalnum(*sec) && *sec != ' ')
                sec++;
        }
    }
    return tolower(*fir) - tolower(*sec);
}


/*
int strcmpReverse(char* fir, char* sec) {
    int i;

    for (i = 0; fir[i] == sec[i]; i++)
        if (fir[i] == '\0')
            return 0;
    return sec[i] - fir[i];
}
*/
