#ifndef STACK_H
#define STACK_H

#define TYPE_CONDITION(type) (type == IDENTIFIER || type == INT_LITERAL || \
                                type == STRING_LITERAL || type == FLOAT_LITERAL || \
                                type == PRINT_FORMAT)

typedef struct s {
    int *type;
    int top;
    int maxSize;
}Stack;

Stack* newStack() {
    Stack *newstack = (Stack*) malloc(sizeof(Stack));
    newstack->maxSize = 16;
    newstack->type = (int*) malloc(newstack->maxSize * sizeof(int));
    newstack->top = -1;

    return newstack;
}

void push(int type, Stack *s) {
    if(s->top >= s->maxSize) {
        s->maxSize *= 2;
        s->type = (int*) realloc(s->type, s->maxSize);
    }

    s->type[++s->top] = type;
}

int pop(Stack *s) {
    int type = s->type[s->top];
    if(s->top > -1)
        s->top -= 1;

    if(s->top < s->maxSize/2) {
        s->maxSize /= 2;
        s->type = (int*) realloc(s->type, s->maxSize);
    }

    return type;
}

void display(Stack s) {
    int i;
    printf("\n\nStack: ");
    for(i = s.top; i >= 0; i--) {
        if(s.type[i] < 74)
            printf("\t%s\n", Types_str[s.type[i]]);
        else
            printf("\t%s\n", Var_str[s.type[i] - 74]);
    }
}

#endif