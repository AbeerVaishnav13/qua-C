#ifndef DATATYPES_H
#define DATATYPES_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef enum t {
    // CLASSES
    IDENTIFIER, // function/variable name
    INT_LITERAL, // interger number
    STRING_LITERAL, // "surrounded by double quotes"
    END_OF_FILE, // EOF

    // TOKENS
    IF, // if
    ELSE, // else
    ELIF, // elif
    WHILE, //while
    FOR, // for
    IN, // in
    FUNC, //func
    NEW, // new
    RETURN, // return
    QUREG, // quReg
    QUBIT, // quBit
    END_OF_BLOCK, // :end
    EXPR_PARANTHESIS_OPEN, EXPR_PARANTHESIS_CLOSE, // (.)
    IDX_BRACKET_OPEN, IDX_BRACKET_CLOSE, // [.]
    CMPND_STMT_OPEN, CMPND_STMT_CLOSE, // {.}
    COMMA, SEMICOLON, COLON, COLON_COLON, GATE_SEPARATOR, // ([H | H])
    PRINT_FORMAT, PRINT, SAVE, // print, save, NON_ZERO, ALL
    INT, CHAR, BOOL, VOID, // Int, Char, Bool, Void
    RANGE, // (2...10)
    IDENTIFIER_DOT, // arr[0].param
    REAL, IMAG, // qr[0].real

    // OPERATORS
    INC, DEC, NEG, BIT_AND, BIT_OR, BIT_EXOR, INV, // Unary operators
    ADD, SUB, MULT, DIV, ASSIGN, EQUALS, GT, LT, GTET, LTET, AND, OR, // Binary Operators
    IF_THEN_ELSE, // Ternary operator
    APPLY_GATES, // (->)
    SEND_TO_FUNC, // (<=)

    // GATES
    NOOP, // ~
    HADAMARD, // H
    PAULI_X, // X
    PAULI_Y, // Y
    PAULI_Z, // Z
    ROTATION, // R_xx.xx
    PHASE, // S
    CNOT_o, // Co
    CNOT_x, // Cx
    SWAP, // Sx
    QFT, // Q
    INV_QFT, // Qi

    // EXTRAS
    NOT_FOUND // instead of returning -1 in getHM()
}Type;

// TODO: make one HashMap with multiple key values

typedef struct kt {
    char key[7];
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
    bool present = false;
    for(i = 0; i < hm->len; i++) {
        if(strcmp(hm->kt[hm->len].key, k) == 0)
            present = true;
    }

    if(hm->len == hm->maxSize) {
        int enlarge = hm->maxSize * 2;
        hm->kt = (KeyTypes*) realloc(hm->kt, enlarge * sizeof(KeyTypes));
        hm->maxSize = enlarge;
        printf("Enlarged to %d\n", hm->maxSize);
    }
    if(!present) {
        strcpy(hm->kt[hm->len].key, k);
        hm->kt[hm->len].type = t;
        hm->len++;
    }
}

Type getHM(HashMap *hm, char k[]) {
    int i;
    for(i = 0; i < hm->len; i++) {
        if(strcmp(hm->kt[i].key, k) == 0)
            return hm->kt[i].type;
    }
    return NOT_FOUND;
}

#endif