#ifndef LEXER_H
#define LEXER_H

#include "Types.h"
#include "HashMap.h"

#define BRACKET_CONDITION_OPEN(c) (c == '(' || c == '[' || c == '{')
#define BRACKET_CONDITION_CLOSE(c) (c == ')' || c == ']' || c == '}')

#define PUNCTUATION_CONDITION(c) (c == '=' || c == '<' || c == '>' || c == ',' || \
                                    c == '-' || c == ':' || c == ';' || c == '|' || c == '~' || c == '@')

void assignType(HashMap *hm, char buf[]) {
    bool Float = false;
    int i;

    for(i = 0; buf[i] != '\0'; i++)
        if(buf[i] == '.')
            Float = true;

    if(!strcmp(buf, "{")) {insertHM(hm, buf, CMPND_STMT_OPEN);}
    else if(!strcmp(buf, "{")) {insertHM(hm, buf, CMPND_STMT_OPEN);}
    else if(!strcmp(buf, "}")) {insertHM(hm, buf, CMPND_STMT_CLOSE);}
    else if(!strcmp(buf, "[")) {insertHM(hm, buf, IDX_BRACKET_OPEN);}
    else if(!strcmp(buf, "]")) {insertHM(hm, buf, IDX_BRACKET_CLOSE);}
    else if(!strcmp(buf, "(")) {insertHM(hm, buf, EXPR_PARANTHESIS_OPEN);}
    else if(!strcmp(buf, ")")) {insertHM(hm, buf, EXPR_PARANTHESIS_CLOSE);}
    else if(!strcmp(buf, ",")) {insertHM(hm, buf, COMMA);}
    else if(!strcmp(buf, "if")) {insertHM(hm, buf, IF);}
    else if(!strcmp(buf, "else")) {insertHM(hm, buf, ELSE);}
    else if(!strcmp(buf, "elif")) {insertHM(hm, buf, ELIF);}
    else if(!strcmp(buf, ";")) {insertHM(hm, buf, END_OF_LINE);}
    else if(!strcmp(buf, "for")) {insertHM(hm, buf, FOR);}
    else if(!strcmp(buf, "func")) {insertHM(hm, buf, FUNC);}
    else if(!strcmp(buf, "|")) {insertHM(hm, buf, GATE_SEPARATOR);}
    else if(!strcmp(buf, ".")) {insertHM(hm, buf, IDENTIFIER_DOT);}
    else if(!strcmp(buf, "in")) {insertHM(hm, buf, IN);}
    else if(!strcmp(buf, "new")) {insertHM(hm, buf, NEW);}
    else if(!strcmp(buf, "NON_ZERO")) {insertHM(hm, buf, PRINT_FORMAT);}
    else if(!strcmp(buf, "ALL")) {insertHM(hm, buf, PRINT_FORMAT);}
    else if(!strcmp(buf, "print")) {insertHM(hm, buf, PRINT);}
    else if(!strcmp(buf, "Qureg")) {insertHM(hm, buf, QUREG);}
    else if(!strcmp(buf, "Qubit")) {insertHM(hm, buf, QUBIT);}
    else if(!strcmp(buf, "class")) {insertHM(hm, buf, CLASS);}
    else if(!strcmp(buf, "inherits")) {insertHM(hm, buf, INHERITS);}
    else if(!strcmp(buf, "@")) {insertHM(hm, buf, EXPLICIT_TYPE_ASSIGN);}
    else if(!strcmp(buf, "private")) {insertHM(hm, buf, ACCESS_SPEC);}
    else if(!strcmp(buf, "protected")) {insertHM(hm, buf, ACCESS_SPEC);}
    else if(!strcmp(buf, "public")) {insertHM(hm, buf, ACCESS_SPEC);}
    else if(!strcmp(buf, "default")) {insertHM(hm, buf, ACCESS_SPEC);}
    else if(!strcmp(buf, "static")) {insertHM(hm, buf, STATIC);}
    else if(!strcmp(buf, "true")) {insertHM(hm, buf, BOOL_LITERAL);}
    else if(!strcmp(buf, "false")) {insertHM(hm, buf, BOOL_LITERAL);}
    else if(!strcmp(buf, "::")) {insertHM(hm, buf, RANGE);}
    else if(!strcmp(buf, "return")) {insertHM(hm, buf, RETURN);}
    else if(!strcmp(buf, "save")) {insertHM(hm, buf, SAVE);}
    else if(!strcmp(buf, "var")) {insertHM(hm, buf, VAR);}
    else if(!strcmp(buf, "val")) {insertHM(hm, buf, VAL);}
    else if(!strcmp(buf, "Int")) {insertHM(hm, buf, INT);}
    else if(!strcmp(buf, "Char")) {insertHM(hm, buf, CHAR);}
    else if(!strcmp(buf, "Bool")) {insertHM(hm, buf, BOOL);}
    else if(!strcmp(buf, "Float")) {insertHM(hm, buf, FLOAT);}
    else if(!strcmp(buf, "String")) {insertHM(hm, buf, STRING);}
    else if(!strcmp(buf, "while")) {insertHM(hm, buf, WHILE);}
    else if(!strcmp(buf, "->")) {insertHM(hm, buf, APPLY_GATES);}
    else if(!strcmp(buf, "++")) {insertHM(hm, buf, INC);}
    else if(!strcmp(buf, "--")) {insertHM(hm, buf, DEC);}
    else if(!strcmp(buf, "&")) {insertHM(hm, buf, BIT_AND);}
    else if(!strcmp(buf, "`")) {insertHM(hm, buf, BIT_INV);}
    else if(!strcmp(buf, "^")) {insertHM(hm, buf, BIT_EXOR);}
    else if(!strcmp(buf, "+")) {insertHM(hm, buf, ADD);}
    else if(!strcmp(buf, "-")) {insertHM(hm, buf, SUB);}
    else if(!strcmp(buf, "*")) {insertHM(hm, buf, MULT);}
    else if(!strcmp(buf, "/")) {insertHM(hm, buf, DIV);}
    else if(!strcmp(buf, "=")) {insertHM(hm, buf, ASSIGN);}
    else if(!strcmp(buf, "==")) {insertHM(hm, buf, EQUALS);}
    else if(!strcmp(buf, "!=")) {insertHM(hm, buf, N_EQUALS);}
    else if(!strcmp(buf, ">")) {insertHM(hm, buf, GT);}
    else if(!strcmp(buf, "<")) {insertHM(hm, buf, LT);}
    else if(!strcmp(buf, ">=")) {insertHM(hm, buf, GTET);}
    else if(!strcmp(buf, "and")) {insertHM(hm, buf, AND);}
    else if(!strcmp(buf, "or")) {insertHM(hm, buf, OR);}
    else if(!strcmp(buf, "+=")) {insertHM(hm, buf, ADD_ASSIGN);}
    else if(!strcmp(buf, "-=")) {insertHM(hm, buf, SUB_ASSIGN);}
    else if(!strcmp(buf, "?")) {insertHM(hm, buf, IF_THEN_ELSE);}
    else if(!strcmp(buf, ":")) {insertHM(hm, buf, IF_THEN_ELSE);}
    else if(!strcmp(buf, "<-")) {insertHM(hm, buf, TX_TO_FUNC);}
    else if(!strcmp(buf, "=>")) {insertHM(hm, buf, RX_FROM_FUNC);}
    else if(!strcmp(buf, "Co")) {insertHM(hm, buf, CNOT_o);}
    else if(!strcmp(buf, "Cx")) {insertHM(hm, buf, CNOT_x);}
    else if(!strcmp(buf, "H")) {insertHM(hm, buf, HADAMARD);}
    else if(!strcmp(buf, "Qi")) {insertHM(hm, buf, INV_QFT);}
    else if(!strcmp(buf, "~")) {insertHM(hm, buf, NOOP);}
    else if(!strcmp(buf, "X")) {insertHM(hm, buf, PAULI_X);}
    else if(!strcmp(buf, "Y")) {insertHM(hm, buf, PAULI_Y);}
    else if(!strcmp(buf, "Z")) {insertHM(hm, buf, PAULI_Z);}
    else if(!strcmp(buf, "S")) {insertHM(hm, buf, PHASE);}
    else if(buf[0] == 'R' && buf[1] == '_' && isdigit(buf[2])) {insertHM(hm, buf, ROTATION);}
    else if(!strcmp(buf, "Sx")) {insertHM(hm, buf, SWAP);}
    else if(Float) {insertHM(hm, buf, FLOAT_LITERAL);}
    else if(isdigit(buf[0])) {insertHM(hm, buf, INT_LITERAL);}
    else if(buf[0] == '"') {
        int i;
        for(i = 0; buf[i] != '\0'; i++);
        buf[i-1] = '\0';
        insertHM(hm, (buf+1), STRING_LITERAL);
    }
    else if(buf[0] == '\'') {
        buf[2] = '\0';
        insertHM(hm, (buf+1), CHAR_LITERAL);
    }
    else {insertHM(hm, buf, IDENTIFIER);}
}

HashMap* Tokenize(FILE *fp) {
	bool alpha = false, digit = false, punct = false, bracket_open = false, bracket_close = false, dot = false;
    bool range = false;
	char buf[80];
	int j = 0;
    char c;

    HashMap *hm = newHashMap();

    while((c = fgetc(fp)) != EOF) {
        if(c == '#') {
            while((c = fgetc(fp)) != '\n' || c == EOF);
        }
		else if(isalpha(c) || c == '_') {
            while(isalpha(c) || c == '_') {
                if(punct || digit || bracket_open || bracket_close || dot) {
                    punct = digit = bracket_open = bracket_close = dot = false;
                    buf[j] = '\0';
                    if(buf[0] != '\0') {assignType(hm, buf);}
                    j = 0;
                }
                alpha = true;
                buf[j++] = c;

                c = fgetc(fp);
            }
            fseek(fp, -1, SEEK_CUR);
		}
		else if(isdigit(c)) {
            while(isdigit(c)) {
                if(alpha) {
                    buf[j++] = c;
                }
                else if(punct || bracket_open || bracket_close || dot) {
                    punct = bracket_open = bracket_close = dot = false;
                    buf[j] = '\0';
                    if(buf[0] != '\0') {assignType(hm, buf);}
                    j = 0;
                }
                if(!alpha && !bracket_open && !bracket_close && !punct && !dot) {
                    digit = true;
                    buf[j++] = c;
                }

                c = fgetc(fp);
            }
            fseek(fp, -1, SEEK_CUR);
		}
        else if(c == '.') {
            char ch = fgetc(fp);
            fseek(fp, -1, SEEK_CUR);

            if(digit && ch != '.') {
                buf[j++] = c;
            }
            else if(alpha || bracket_close || bracket_open || punct || digit) {
                alpha = bracket_close = bracket_open = punct = digit = false;
                buf[j] = '\0';
                if(buf[0] != '\0') {assignType(hm, buf);}
                j = 0;

                dot = true;
                buf[j++] = c;
            }
            else if(dot) {
                buf[j++] = c;
            }
        }
		else if(PUNCTUATION_CONDITION(c)) {
            while(PUNCTUATION_CONDITION(c)) {
                if(alpha || digit || bracket_open || bracket_close || dot) {
                    alpha = digit = bracket_open = bracket_close = dot = false;
                    buf[j] = '\0';
                    if(buf[0] != '\0') {assignType(hm, buf);}
                    j = 0;
                }

                punct = true;
                buf[j++] = c;

                c = fgetc(fp);
            }
            fseek(fp, -1, SEEK_CUR);
		}
        else if(BRACKET_CONDITION_OPEN(c)) {
            while (BRACKET_CONDITION_OPEN(c)) {
                if(alpha || digit || punct || bracket_close || dot) {
                    alpha = digit = punct = bracket_close = dot = false;
                    buf[j] = '\0';
                    if(buf[0] != '\0') {assignType(hm, buf);}
                    j = 0;
                }
                bracket_open = true;
                if(j == 0)
                    buf[j++] = c;
                else {
                    buf[j] = '\0';
                    if(buf[0] != '\0') {assignType(hm, buf);}
                    j = 0;
                    fseek(fp, -1, SEEK_CUR);
                }

                c = fgetc(fp);
            }
            fseek(fp, -1, SEEK_CUR);
        }
        else if(BRACKET_CONDITION_CLOSE(c)) {
            while (BRACKET_CONDITION_CLOSE(c)) {
                if(alpha || digit || punct || bracket_open || dot) {
                    alpha = digit = punct = bracket_open = dot = false;
                    buf[j] = '\0';
                    if(buf[0] != '\0') {assignType(hm, buf);}
                    j = 0;
                }
                bracket_close = true;
                if(j == 0)
                    buf[j++] = c;
                else {
                    buf[j] = '\0';
                    if(buf[0] != '\0') {assignType(hm, buf);}
                    j = 0;
                    fseek(fp, -1, SEEK_CUR);
                }

                c = fgetc(fp);
            }
            fseek(fp, -1, SEEK_CUR);
        }
        else if(c == '"' || c == '\'') {
            if(c == '"') {
                if(alpha || digit || punct || bracket_close || bracket_open) {
                    alpha = digit = punct = bracket_close = bracket_open = dot = false;
                    buf[j] = '\0';
                    if(buf[0] != '\0') {assignType(hm, buf);}
                    j = 0;
                }

                buf[j++] = c;
                while((c = fgetc(fp)) != '"') {
                    buf[j++] = c;
                }
                buf[j] = c;
                buf[j+1] = '\0';
                if(buf[0] != '\0') {assignType(hm, buf);}
                j = 0;
            }
            else {
                buf[j++] = c;
                while ((c = fgetc(fp)) != '\'') {
                    buf[j++] = c;
                }
                buf[j] = c;
                buf[j+1] = '\0';
                if(buf[0] != '\0') {assignType(hm, buf);}
                j = 0;
            }
        }
		else if(c == ' ' || c == '\n' || c == '\t') {
            while(c == ' ' || c == '\n' || c == '\t') {
                if(alpha || digit || punct || bracket_close || bracket_open || dot) {
                    alpha = digit = punct = bracket_open = bracket_close = dot = false;
                    buf[j] = '\0';
                    if(buf[0] != '\0') {assignType(hm, buf);}
                    j = 0;
                }

                c = fgetc(fp);
            }
            char ch = fgetc(fp);
            if(ch != EOF) {
            	fseek(fp, -2, SEEK_CUR);
            }
            else if(ch == EOF && (c != '\n' || c == ' ' || c == '\t')) {
                alpha = digit = punct = bracket_open = bracket_close = dot = false;
                buf[j++] = c;
                buf[j] = '\0';
                if(buf[0] != '\0') {assignType(hm, buf);}
                j = 0;
            }
		}
	}

    return hm;
}

#endif