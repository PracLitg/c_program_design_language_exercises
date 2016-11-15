#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "../../libraries/iolines/iolines.h"

#define MAXWORD 100
#define MAXNODES 200

struct tnode {
    char* word;
    int count;
    struct tnode* left;
    struct tnode* right;
};

static struct tnode* tree_nodes[MAXNODES];
static int node_index = 0;

struct tnode* addTree(struct tnode*, char*);
char* myStrdup(char* s);
void getTreeNodes(struct tnode*);
void treePrint();
int compare(const void*, const void*);
void freeTree();


int main(int argc, char const *argv[]) {
    struct tnode* root;
    char word[MAXWORD];
    int c;

    root = NULL;
    while ((c = getword(word, MAXWORD)) != EOF) {
        if (isalpha(c) || c == '_') {
            root = addTree(root, word);
        }
    }

    getTreeNodes(root);
    qsort(tree_nodes, node_index, sizeof(struct tnode*), compare);
    treePrint();
    freeTree();
    return 0;
}


struct tnode* addTree(struct tnode* p, char* w) {
    int cond;

    if (p == NULL) {
        p = (struct tnode*)malloc(sizeof(struct tnode));
        p->word = myStrdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0) {
        p->count++;
    } else if (cond < 0) {
        p->left = addTree(p->left, w);
    } else if (cond > 0) {
        p->right = addTree(p->right, w);
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


void getTreeNodes(struct tnode* p) {
    int i;

    if (p != NULL) {
        getTreeNodes(p->left);
        tree_nodes[node_index++] = p;
        getTreeNodes(p->right);
    }
}


int compare(const void* a, const void* b) {
    return (*(struct tnode**)a)->count - (*(struct tnode**)b)->count;
}


void treePrint() {
    int i;

    for (i = 0; i < node_index; i++) {
        printf("%d %s\n", tree_nodes[i]->count, tree_nodes[i]->word);
    }
}


void freeTree() {
    int i;

    for (i = 0; i < node_index; i++) {
        free(tree_nodes[i]->word);
        free(tree_nodes[i]);
    }
}
