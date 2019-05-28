#ifndef SYNTAXANALYSER_H
#define SYNTAXANALYSER_H

#define IS_DATATYPE(d) (d == INT || d == CHAR || d == FLOAT || \
                        d ==  BOOL || d == QUREG || d == QUBIT)

bool reduce(Stack *s, Production *p, int len) {
    int *buf = (int*) malloc(len * sizeof(int));
    int j, k;

    if(len-1 > s->top) {
        printf("\nlen = %d > s->top", len);
        return false;
    }

    for(j = 0; j < len; j++) {
        buf[len-j-1] = s->type[s->top - j];
        printf("Copied in buffer: %d", len);
    }

    int start, end;
    if(len == 1) {start = 0; end = ONE_PRODUCTION; printf("\nstart = %d, end = %d", start, end);}
    else if(len == 2) {start = ONE_PRODUCTION; end = TWO_PRODUCTION; printf("\nstart = %d, end = %d", start, end);}
    else if(len == 3) {start = TWO_PRODUCTION; end = THREE_PRODUCTION; printf("\nstart = %d, end = %d", start, end);}
    else if(len == 4) {start = THREE_PRODUCTION; end = FOUR_PRODUCTION; printf("\nstart = %d, end = %d", start, end);}
    else if(len == 5) {start = FOUR_PRODUCTION; end = FIVE_PRODUCTION; printf("\nstart = %d, end = %d", start, end);}
    else if(len == 8) {start = FIVE_PRODUCTION; end = EIGHT_PRODUCTION; printf("\nstart = %d, end = %d", start, end);}
    else if(len == 9) {start = EIGHT_PRODUCTION; end = NINE_PRODUCTION; printf("\nstart = %d, end = %d", start, end);}

    for(j = start; j < end; j++) {
        printf("Entered loop");
        if(isEqual(p[j].beta, buf, len)) {
            printf("Matched a production!");
            if(s->type[s->top] == functions && s->top == 0) {
                s->type[s->top] = library;
            }
            else if(len == 1 && buf[0] == IDENTIFIER) {
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
                printf("\nPushed: %s", Var_str[p[j].alpha - 74]);
                push(p[j].alpha, s);
            }
            return true;
        }
    }

    return false;
}

void shift(int type, Stack *s) {
    push(type, s);
}

bool syntaxCheck(HashMap *hm) {
    Stack *s = newStack();
    int i = 0;

    Production *prod;
    initProductions(prod);

    push(hm->kt[i++].type, s);
    
    while(s->type[s->top] != library) {
        display(*s);
        if(reduce(s, prod, 1)) {printf("\ntaken: Reduce-1"); continue;} // Reduce-1 step
        else if(reduce(s, prod, 2)) {printf("\ntaken: Reduce-2"); continue;} // Reduce-2 step
        else if(reduce(s, prod, 3)) {printf("\ntaken: Reduce-3"); continue;} // Reduce-3 step
        else if(reduce(s, prod, 4)) {printf("\ntaken: Reduce-4"); continue;} // Reduce-4 step
        else if(reduce(s, prod, 5)) {printf("\ntaken: Reduce-5"); continue;} // Reduce-5 step
        else if(reduce(s, prod, 8)) {printf("\ntaken: Reduce-8"); continue;} // Reduce-8 step
        else if(reduce(s, prod, 9)) {printf("\ntaken: Reduce-9"); continue;} // Reduce-9 step
        else {printf("\ntaken: shift"); shift(hm->kt[i++].type, s);} // Shift step

        if(i > hm->len) {
            return false;
        }
    }
    return true;
}

#endif