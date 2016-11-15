#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "../../libraries/iolines/iolines.h"

#define MAXLEN 100

enum match {YES, NO};
static int signal;

struct tnode {
    char* word;
    int mc;
    int sign;
    struct tnode* left;
    struct tnode* right;
};

struct tnode* addtree(struct tnode*, char*, int num, int*, int*);
char* myStrdup(char*);
int compare(struct tnode*, char*, int, int*, int*);
void treeprint(struct tnode*, int);


int main(int argc, char const *argv[]) {
    struct tnode* root;
    char word[MAXLEN];
    int num, found, sign;

    root = NULL;
    num = 6;
    while (getword(word, MAXLEN) != EOF) {
        found = NO;
        sign = 0;
        if ((isalpha(word[0]) || word[0] == '_') && strlen(word) >= num) {
            root = addtree(root, word, num, &found, &sign);
        }
    }

    int i;
    for (i = 1; i <= signal; i++) {
        treeprint(root, i);
    }
    return 0;
}


struct tnode* addtree(struct tnode* p, char* w, int num, int* found, int* sign) {
    int cond;

    if (p == NULL) {
        //printf("%d\n", *found);
        p = (struct tnode*)malloc(sizeof(struct tnode));
        p->word = myStrdup(w);
        p->mc = *found;
        p->sign = *sign;
        p->left = p->right = NULL;
    } else if ((cond = compare(p, w, num, found, sign)) < 0) {
        p->left = addtree(p->left, w, num, found, sign);
    } else if (cond > 0) {
        p->right = addtree(p->right, w, num, found, sign);
    }
    return p;
}


char* myStrdup(char* s) {
    char* p;

    p = (char*)malloc(strlen(s) + 1);
    if (p != NULL) {
        strcpy(p, s);
    }
    return p;
}


int compare(struct tnode* p, char* w, int num, int* found, int* sign) {
    char* s;
    char* t;

    s = w;
    t = p->word;
    while (*s == *t) {
        if (*s == '\0') {
            return 0;
        }
        s++;
        t++;
    }
    if ((s - w) >= num) {
        if (p->mc == YES) {
            *sign = p->sign;
        } else {
            *sign = ++signal;
            p->sign = signal;
            p->mc = YES;
        }
        *found = YES;
    }
    return *s - *t;
}


void treeprint(struct tnode* p, int cnt) {
    if (p != NULL) {
        treeprint(p->left, cnt);
        if (p->mc == YES && p->sign == cnt) {
            printf("%s\n", p->word);
        }
        treeprint(p->right, cnt);
    }
}
