#include <stdio.h>

int searchComment() {
    int c = getchar();
    if (c == '/') {
        while ((c = getchar()) != '\n')
            ;
        return 1;
    } else if (c == '*') {
        while (c = getchar() != EOF) {
            if (c == '*') {
                c = getchar();
                if (c == '/') return 1;
            }
        }
    }
    return 0;
}

int searchQuotation() {
    int c;
    while ((c = getchar()) != EOF) {
        if (c == '"') return 1;
    }
    return 0;
}

int searchSingleQuote() {
    int c;
    while ((c = getchar()) != EOF) {
        if (c == '\'') return 1;
    }
    return 0;
}


int main() {
    int anno_num = 0, ro_bra_num = 0, sq_bra_num = 0,
            fl_bra_num = 0;
    int c;
    while ((c = getchar()) != EOF) {
        if (c == '\'') {
            if (!searchSingleQuote())
                printf("Single Quotation Lost\n");
        } else if (c == '"') {
            if (!searchQuotation())
                printf("Quotation Lost\n");
        } else if (c == '*') {
            c = getchar();
            if (c == '/') anno_num--;
        } else if (c == '/') {
            if (!searchComment()) {
                printf("Annotation Lost\n");
            }
        } else if (c == '{') {
            fl_bra_num++;
        } else if (c == '[') {
            sq_bra_num++;
        } else if (c == '(') {
            ro_bra_num++;
        } else if (c == '}') {
            fl_bra_num--;
        } else if (c == ']') {
            sq_bra_num--;
        } else if (c == ')') {
            ro_bra_num--;
        }
    }
    if (anno_num == 0 && ro_bra_num == 0 && sq_bra_num == 0
        && fl_bra_num == 0) {
        printf("Format Correct\n");
    } else {
        printf("Format Error\n");
    }
    return 0;
}
