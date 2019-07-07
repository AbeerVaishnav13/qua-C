#ifndef SYNTAXANALYSER_H
#define SYNTAXANALYSER_H

#include "Stack.h"
#include "Types.h"
#include "Grammer.h"
#include "HashMap.h"

#define IS_DATATYPE(d) (d == VAR || d == VAL || d == QUREG || d == QUBIT)

bool parse(Stack *s, int start, int end, unsigned int hashed_prod, int len, unsigned int alpha[], unsigned int beta[]){
    int j, k;

    for(j = start; j < end; j++) {
        // printf("Entered loop");
        if(beta[j] == hashed_prod) {
            printf("\n\n\nMatched a production!");
            if(s->type[s->top] == functions && s->top == 0) {
                s->type[s->top] = library;
            }
            else if(len == 1 && hashed_prod == hashItSingle(IDENTIFIER)) {
                int a = pop(s);
                printf("\nPopped: %s", ((a < 74) ? Types_str[a] : Var_str[a - 74]));
                if(IS_DATATYPE(s->type[s->top - 1])) {
                    printf("\nPushed: %s", Var_str[vardef_single - 74]);
                    push(vardef_single, s);
                }
                else {
                    printf("\nPushed: %s", Var_str[expr - 74]);
                    push(expr, s);
                }
            }
            else {
                for(k = 0; k < len; k++) {
                    int idx = pop(s);
                    printf("\nPopped: %s", ((idx < 74) ? Types_str[idx] : Var_str[idx - 74]));
                }
                printf("\nPushed: %s", Var_str[alpha[j] - 74]);
                push(alpha[j], s);
            }
            return true;
        }
    }

    return false;
}

bool reduce(Stack *s, int len) {
    int *buf = (int*) malloc(len * sizeof(int));
    int j, k;
    bool parsed = false;

    if(len-1 > s->top) {
        printf("\nlen = %d > s->top", len);
        return false;
    }

    for(j = 0; j < len; j++) {
        buf[len-j-1] = s->type[s->top - j];
        // printf("Copied in buffer: %d", len);
    }

    unsigned int hashed_prod = hashIt(buf, len);

    if(len == 1) {parsed = parse(s, 0, ONE_PRODUCTION, hashed_prod, len, alpha1, beta1);}
    else if(len == 2) {parsed = parse(s, ONE_PRODUCTION, TWO_PRODUCTION, hashed_prod, len, alpha2, beta2);}
    else if(len == 3) {parsed = parse(s, TWO_PRODUCTION, THREE_PRODUCTION, hashed_prod, len, alpha3, beta3);}
    else if(len == 4) {parsed = parse(s, THREE_PRODUCTION, FOUR_PRODUCTION, hashed_prod, len, alpha4, beta4);}
    else if(len == 5) {parsed = parse(s, FOUR_PRODUCTION, FIVE_PRODUCTION, hashed_prod, len, alpha5, beta5);}
    else if(len == 8) {parsed = parse(s, FIVE_PRODUCTION, EIGHT_PRODUCTION, hashed_prod, len, alpha8, beta8);}
    else if(len == 9) {parsed = parse(s, EIGHT_PRODUCTION, NINE_PRODUCTION, hashed_prod, len, alpha9, beta9);}

    return parsed;
}

void shift(int type, Stack *s) {
    push(type, s);
}

bool syntaxCheck(Type *tokens, int len) {
    Stack *s = newStack();
    int i = 0;

    push(tokens[i++], s);
    
    while(s->type[s->top] != library) {
        displayStack(*s);
        if(reduce(s, 1)) {printf("\ntaken: Reduce-1"); continue;} // Reduce-1 step
        else if(reduce(s, 2)) {printf("\ntaken: Reduce-2"); continue;} // Reduce-2 step
        else if(reduce(s, 3)) {printf("\ntaken: Reduce-3"); continue;} // Reduce-3 step
        else if(reduce(s, 4)) {printf("\ntaken: Reduce-4"); continue;} // Reduce-4 step
        else if(reduce(s, 5)) {printf("\ntaken: Reduce-5"); continue;} // Reduce-5 step
        else if(reduce(s, 8)) {printf("\ntaken: Reduce-8"); continue;} // Reduce-8 step
        else if(reduce(s, 9)) {printf("\ntaken: Reduce-9"); continue;} // Reduce-9 step
        else {printf("\ntaken: shift"); shift(tokens[i++], s);} // Shift step

        if(i > len) {
            return false;
        }
    }
    return true;
}

#endif