#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "../../libraries/iolines/iolines.h"

#define MAXCOUNT 50
#define MAXWORD 100
#define MAXNODES 200

struct tnode {
    char* word;
    int* lines;
    int pos;
    struct tnode* left;
    struct tnode* right;
};

static int line_num = 1;
static struct tnode* tree_nodes[MAXNODES];
static int node_index = 0;

struct tnode* addtree(struct tnode*, char*);
int myGetWord(char*, int);
void treeprint(struct tnode*);
char* myStrdup(char* s);
void freeTree();


int main() {
    struct tnode* root;
    char word[MAXWORD];
    int c;

    root = NULL;
    while ((c = myGetWord(word, MAXWORD)) != EOF) {
        if (isalpha(c) || c == '_') {
            root = addtree(root, word);
        } else if (c == '\n') {
            line_num++;
        }
    }

    treeprint(root);

    freeTree();
    return 0;
}


struct tnode* addtree(struct tnode* p, char* w) {
    int cond;

    if (p == NULL) {
        p = (struct tnode*)malloc(sizeof(struct tnode));
        p->word = myStrdup(w);
        p->lines = (int*)malloc(sizeof(int)*MAXCOUNT);
        memset(p->lines, 0, sizeof(MAXCOUNT));
        p->pos = 0;
        p->lines[p->pos] = line_num;
        p->pos += 1;
        //printf("%d\n", p->pos);
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0) {
        p->lines[p->pos] = line_num;
        p->pos += 1;
    } else if (cond < 0) {
        p->left = addtree(p->left, w);
    } else {
        p->right = addtree(p->right, w);
    }
    return p;
}


// this function can get the letter '\n'
int myGetWord(char* word, int lim) {
    int c;
    char* w = word;

    while (isspace(c = getch()) && c != '\n') {
        ;
    }

    if (c != EOF) {
        *w++ = c;
    }
    if (isalpha(c) || c == '#' || c == '_') {
        for (; --lim > 0; w++) {
            if (!isalnum(*w = getch()) && *w != '_') {
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


char* myStrdup(char* s) {
    char* p;

    p = (char*)malloc(strlen(s) + 1);
    if (p != NULL) {
        strcpy(p, s);
    }
    return p;
}


void treeprint(struct tnode* p) {
    int i;

    if (p != NULL) {
        treeprint(p->left);
        tree_nodes[node_index++] = p;
        printf("%s: ", p->word);
        for (i = 0; i < p->pos; i++) {
            printf("%d ", p->lines[i]);
        }
        printf("\n");
        treeprint(p->right);
    }
}


void freeTree() {
    int i;

    for (i = 0; i < node_index; i++) {
        free(tree_nodes[i]->word);
        free(tree_nodes[i]->lines);
        free(tree_nodes[i]);
    }
}
