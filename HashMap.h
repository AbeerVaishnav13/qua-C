#ifndef HASHMAP_H
#define HASHMAP_H

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

// CURRENTLY BASED ON LINEAR SEARCH
// Mostly will not be used as the map itself will be the input to the Parser
// Type getHM(HashMap *hm, char k[]) {
//     int i;
//     for(i = 0; i < hm->len; i++) {
//         if(strcmp(hm->kt[i].key, k) == 0)
//             return hm->kt[i].type;
//     }
//     return NOT_FOUND;
// }

void displayMap(HashMap hm) {
    int i;
    for(i = 0; i < hm.len; i++) {
        printf("'%s' : %s\n", hm.kt[i].key, Types_str[hm.kt[i].type]);
    }
}

#endif