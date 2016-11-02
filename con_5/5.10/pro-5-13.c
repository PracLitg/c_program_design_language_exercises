#include <stdio.h>
#include <ctype.h>

#define MAXLINE 100
#define MAXLEN 100
#define DEFAULTLEN 10

int atoi(char* str) {
    int res = 0;
    while (*str && isdigit(*str))
        res = res * 10 + (*str++ - '0');
    if (*str == '\0')
        return res;

    return -1;
}

int main(int argc, char* argv[]) {
    int c, n;
    n = DEFAULTLEN;
    while (--argc > 0 && (*++argv)[0] == '-')
        while (c = *++argv[0])
            switch (c) {
                case 'n':
                    //printf("%s\n", *(argv + 1));
                    n = atoi(*(argv + 1));
                    break;
                default:
                    n = -1;
                    break;
            }

    if (n != -1) {
        char total_lines[MAXLINE][MAXLINE];
        int cnt = 0;
        while (fgets(total_lines[cnt++], MAXLEN, stdin))
            ;
        int i;
        if (cnt < n) {
            for (int i = 0; i < cnt; i++) {
                printf("%s\n", total_lines[i]);
            }
        } else {
            for (i = 0; i < 10; i++)
                printf("%s", total_lines[cnt - n - 1 + i]);
        }
    } else {
        printf("Tail: Illeagal input");
    }

    return 0;
}
