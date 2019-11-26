#ifndef HASHMAP_H
#define HASHMAP_H

#include "Types.h"

typedef struct kt {
    char *key;
    Type type;
}KeyTypes;

typedef struct hm {
    KeyTypes *kt;
    int len;
    int maxSize;
}HashMap;

HashMap* newHashMap() {
    int MS = 2;
    HashMap *hm = (HashMap*) malloc(sizeof(HashMap));
    hm-> kt = (KeyTypes*) malloc(MS * sizeof(KeyTypes));
    hm->len = 0;
    hm->maxSize = MS;
    return hm;
}

void insertHM(HashMap *hm, char k[], Type t) {
    int i;
    int len = 0;
    for(i = 0; k[i] != '\0'; i++)
        len++;

    if(hm->len == hm->maxSize) {
        int enlarge = hm->maxSize * 2;
        hm->kt = (KeyTypes*) realloc(hm->kt, (enlarge+1) * sizeof(KeyTypes));
        hm->maxSize = enlarge;
        // printf("Enlarged to %d\n", hm->maxSize);
    }

    hm->kt[hm->len].key = (char*) malloc(len * sizeof(char));
    strcpy(hm->kt[hm->len].key, k);
    hm->kt[hm->len].type = t;
    hm->len++;
}

void displayMap(HashMap hm) {
    int i;
    for(i = 0; i < hm.len; i++) {
        printf("'%s' : %s\n", hm.kt[i].key, Types_str[hm.kt[i].type]);
    }
}

Type* toArrayofTypes(HashMap hm) {
    Type *t = (Type*) malloc(hm.len * sizeof(Type));
    int i = 0;
    for(i = 0; i < hm.len; i++)  {
        t[i] = hm.kt[i].type;
    }

    return t;
}

KeyTypes* toArrayOfKeyTypes(HashMap hm) {
    KeyTypes *kt = (KeyTypes*) malloc(hm.len * sizeof(KeyTypes));
    int i;
    for(i = 0; i < hm.len; i++) {
        kt[i].key = (char*) malloc(strlen(hm.kt[i].key) * sizeof(char));
        strcpy(kt[i].key, hm.kt[i].key);
        kt[i].type = hm.kt[i].type;
    }

    return kt;
}

#endif