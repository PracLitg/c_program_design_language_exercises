#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../../libraries/iolines/iolines.h"

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

void dcl();
void dirdcl();
int gettoken();

int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];

int main(int argc, char const *argv[]) {
    while (gettoken() != EOF) {
        strcpy(datatype, token);
        out[0] = '\0';
        dcl();
        if (tokentype != '\n')
            printf("Syntax Error");
        printf("%s: %s %s\n", name, out, datatype);
    }
    return 0;
}


int gettoken() {
    int c;
    char* p = token;

    while ((c = getch()) == ' ' || c == '\t')
        ;

    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if (c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']';)
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch()); )
            *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    } else {
        return tokentype = c;
    }
}


void dcl() {
    int ns;

    for (ns = 0; gettoken() == '*';) {
        ns++;
    }
    dirdcl();
    while (ns-- > 0)
        strcat(out, " pointer to");
}

#define BASECNT 6
char* base_type[10] = {"short", "int", "long", "double", "float", "char"};

void dirdcl() {
    int type;

    if (tokentype == '(') {
        dcl();
        if (tokentype != ')')
            printf("Error: Missing )\n");
    } else if (tokentype == NAME) {
        int is_base_type = 0;
        int i;
        for (i = 0; i < BASECNT; i++) {
            if (strcmp(base_type[i], name) == 0) {
                strcat(out, " with parameter of a");
                dcl();
                is_base_type = 1;
                break;
            }
        }
        if (!is_base_type)
            strcpy(name, token);
    } else
        printf("Error: Expected name or (dcl)\n");

    while ((type = gettoken()) == PARENS || type == BRACKETS)
        if (type == PARENS)
            strcat(out, " function returnning");
        else {
            strcat(out, " array ");
            strcat(out, token);
            strcat(out, "of");
        }

    dcl();
}
