#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../../libraries/iolines/iolines.h"

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

void dcl();
void dirdcl();
int gettoken();
int compare(char** s, char** t);
int typespec();
int typeequal();
void dclspec();
void parmdcl();

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

void dirdcl() {
    int type;

    if (tokentype == '(') {
        dcl();
        if (tokentype != ')')
            printf("Error: Missing )\n");
    } else if (tokentype == NAME)
        strcpy(name, token);
    else
        printf("Error: Expected name or (dcl)\n");

    while ((type = gettoken()) == PARENS || type == BRACKETS || type == '(')
        if (type == PARENS)
            strcat(out, " function returnning");
        else if (type == BRACKETS) {
            strcat(out, " array ");
            strcat(out, token);
            strcat(out, "of");
        } else {
            strcat(out, " function expecting");
            parmdcl();
            strcat(out, " and returnning");
        }
}


int compare(char** s, char** t) {
    return strcmp(*s, *t);
}


int typespec() {
    static char* types[] = {
        "char",
        "int",
        "void"
    };

    char* pt = token;

    if (bsearch(&pt, types, sizeof(types) / sizeof(char *), sizeof(char*), compare) == NULL) {
        return NO;
    } else {
        return YES;
    }
}


int typeequal() {
    static char* types[] = {
        "const",
        "volatile"
    };
    char* pt = token;

    if (bsearch(&pt, types, sizeof(types) / sizeof(char *), sizeof(char*), compare) == NULL) {
        return NO;
    } else {
        return YES;
    }
}


void dclspec() {
    char temp[MAXTOKEN];

    temp[0] = '\0';
    gettoken();
    do {
        if (tokentype != NAME) {
            dcl();
        } else if (typespec() == YES) {
            strcat(temp, " ");
        } else if (typeequal() == YES) {
            strcat(temp, " ");
            strcat(temp, token);
            gettoken();
        } else {
            printf("Unknown type in parameter list\n");
        } while (tokentype != ',' && tokentype != ')');
        strcat(out, temp);
        if (tokentype == ',') {
            strcat(out, ",");
        }
    }
}


void parmdcl() {
    do {
        dclspec();
    } while (tokentype == ',');
    if (tokentype != ')')
        printf("Missing ) in parameter declaration\n");
}
