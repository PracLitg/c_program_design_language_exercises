#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "../../libraries/iolines/iolines.h"

#define HASH_SIZE 101
#define MAX_LINES 101
#define MAX_LEN 100

struct nlist {
    struct nlist* next;
    char* name;
    char* defn;
};

static struct nlist* hash_tab[HASH_SIZE];
static char* lineptr[MAX_LINES];

void getNameAndDef(int, char*, char*);
unsigned hash(char* s);
struct nlist* lookUp(char*);
char* myStrdup(char* s);
struct nlist* install(char*, char*);
void printAll();
void clearAll();


int main(int argc, char const *argv[]) {
    int nlines, i;
    char name[MAX_LEN];
    char defn[MAX_LEN];

    memset(hash_tab, 0, HASH_SIZE*sizeof(struct nlist*));
    if ((nlines = readlines(lineptr, MAX_LINES)) >= 0) {
        for (i = 0; i < nlines; i++) {
            getNameAndDef(i, name, defn);
            //printf("%s: %s\n", name, defn);
            install(name, defn);
        }
    }
    printAll();
    clearAll();
    return 0;
}


void getNameAndDef(int idx, char* name, char* defn) {
    int i, len;

    // remove spaces
    for (i = 0; isspace(lineptr[idx][i]); i++)
        ;

    // get name
    for (; isalnum(lineptr[idx][i]) || lineptr[idx][i] == '_'; i++) {
        *name = lineptr[idx][i];
        name++;
    }
    *name = '\0';
    // romove spaces
    for (; isspace(lineptr[idx][i]); i++)
        ;
    // get def
    for (; isalnum(lineptr[idx][i]) || lineptr[idx][i] == '_'; i++) {
        *defn = lineptr[idx][i];
        defn++;
    }
    *defn = '\0';
}


unsigned hash(char* s) {
    unsigned hash_val;

    for (hash_val = 0; *s != '\0'; s++) {
        hash_val = *s + 31 * hash_val;
    }
    return hash_val % HASH_SIZE;
}


struct nlist* lookUp(char* s) {
    struct nlist* np;

    for (np = hash_tab[hash(s)]; np != NULL; np = np->next) {
        if (strcmp(s, np->name) == 0) {
            return np;
        }
    }
    return NULL;
}


char* myStrdup(char* s) {
    char* p;

    p = (char*)malloc(strlen(s) + 1);
    if (p != NULL) {
        strcpy(p, s);
    }
    return p;
}


struct nlist* install(char* name, char* defn) {
    struct nlist* np;
    unsigned hash_val;

    if ((np = lookUp(name)) == NULL) {
        np = (struct nlist*)malloc(sizeof(struct nlist));
        if (np == NULL || (np->name = myStrdup(name)) == NULL) {
            return NULL;
        }
        hash_val = hash(name);
        // inverse order: useful
        np->next = hash_tab[hash_val];
        hash_tab[hash_val] = np;
    } else {
        free((void*)np->defn);
    }
    if ((np->defn = myStrdup(defn)) == NULL) {
        return NULL;
    }
    return np;
}


void printAll() {
    int i;
    struct nlist* np;

    for (i = 0; i < HASH_SIZE; i++) {
        for (np = hash_tab[i]; np != NULL; np = np->next) {
            printf("%12s: %12s\n", np->name, np->defn);
        }
    }
}


void clearAll() {
    int i;
    struct nlist* np, * np2;

    for (i = 0; i < HASH_SIZE; i++) {
        for (np = hash_tab[i], np2 = np; np != NULL;) {
            free(np2->name);
            free(np2->defn);
            np2 = np2->next;
            free(np);
            np = np2;
        }
    }
}
