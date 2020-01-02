#ifndef QUANTUM_LEXER_H
#define QUANTUM_LEXER_H

#define BRACKET_CONDITION_OPEN(c) (c == '(' || c == '[' || c == '{')
#define BRACKET_CONDITION_CLOSE(c) (c == ')' || c == ']' || c == '}')

#define PUNCTUATION_CONDITION(c) (c == '=' || c == ',' || c == '>')

#define GATE_COND_LEX(c) (c == 'X' || c == 'Y' || c == 'Z' || c == 'H' || \
                      c == 'R' || c == '_' || c == '.' || isdigit(c) || \
                      c == 'x' || c == '~' || c == '@' || c == 'o' || \
                      c == '^' || c == '*' || isalnum(c) || c == '-' || \
                      c == '/')

void assignType(HashMap *hm, char buf[]) {
    bool Float = false;
    int i;

    for(i = 0; buf[i] != '\0'; i++)
        if(buf[i] == '.')
            Float = true;

    if(!strcmp(buf, "{")) {insertHM(hm, buf, CMPND_STMT_OPEN);}
    else if(!strcmp(buf, "}")) {insertHM(hm, buf, CMPND_STMT_CLOSE);}
    else if(!strcmp(buf, "[")) {insertHM(hm, buf, IDX_BRACKET_OPEN);}
    else if(!strcmp(buf, "]")) {insertHM(hm, buf, IDX_BRACKET_CLOSE);}
    else if(!strcmp(buf, "(")) {insertHM(hm, buf, EXPR_PARANTHESIS_OPEN);}
    else if(!strcmp(buf, ")")) {insertHM(hm, buf, EXPR_PARANTHESIS_CLOSE);}
    else if(!strcmp(buf, ",")) {insertHM(hm, buf, COMMA);}
    else if(!strcmp(buf, "func")) {insertHM(hm, buf, FUNC);}
    else if(!strcmp(buf, "gate")) {insertHM(hm, buf, GATE);}
    else if(!strcmp(buf, ".")) {insertHM(hm, buf, DOT);}
    else if(!strcmp(buf, "new")) {insertHM(hm, buf, NEW);}
    else if(!strcmp(buf, "Pnz") || !strcmp(buf, "Pa")) {insertHM(hm, buf, PRINT);}
    else if(!strcmp(buf, "quReg")) {insertHM(hm, buf, QUREG);}
    else if(!strcmp(buf, "=>")) {insertHM(hm, buf, REG_NAME);}
    else if(!strcmp(buf, "=")) {insertHM(hm, buf, EQUALS);}
    else if(!strcmp(buf, "$")) {insertHM(hm, buf, LIST_END);}
    else if(!strcmp(buf, "X")) {insertHM(hm, buf, PAULI_X);}
    else if(!strcmp(buf, "Y")) {insertHM(hm, buf, PAULI_Y);}
    else if(!strcmp(buf, "Z")) {insertHM(hm, buf, PAULI_Z);}
    else if(!strcmp(buf, "S")) {insertHM(hm, buf, PHASE);}
    else if(!strcmp(buf, "H")) {insertHM(hm, buf, HADAMARD);}
    else if(!strcmp(buf, "x")) {insertHM(hm, buf, SWAP);}
    else if(!strcmp(buf, "~")) {insertHM(hm, buf, QFT);}
    else if(!strcmp(buf, "@")) {insertHM(hm, buf, CONTROL);}
    else if(!strcmp(buf, "o")) {insertHM(hm, buf, INV_CONTROL);}
    else if(!strcmp(buf, "^")) {insertHM(hm, buf, POWER);}
    else if(!strcmp(buf, "-")) {insertHM(hm, buf, IDENTITY);}
    else if(!strcmp(buf, "Rx")) {insertHM(hm, buf, ROTATION_X);}
    else if(!strcmp(buf, "Ry")) {insertHM(hm, buf, ROTATION_Y);}
    else if(!strcmp(buf, "Rz")) {insertHM(hm, buf, ROTATION_Z);}
    else if(!strcmp(buf, "pi")) {insertHM(hm, buf, MATH_PI);}
    else if(!strcmp(buf, "/")) {insertHM(hm, buf, DIVISION);}
    else if(!strcmp(buf, "*")) {insertHM(hm, buf, MULTIPLICATION);}
    else if(Float) {insertHM(hm, buf, FLOAT_LITERAL);}
    else if(isdigit(buf[0])) {insertHM(hm, buf, INT_LITERAL);}
    else if(buf[0] == '"' || buf[0] == '\'') {
        int i;
        for(i = 0; buf[i] != '\0'; i++);
        buf[i-1] = '\0';
        insertHM(hm, (buf+1), STRING_LITERAL);
    }
    else {insertHM(hm, buf, IDENTIFIER);}
}

HashMap* Tokenize(FILE *fp) {
	bool alpha = false, digit = false, punct = false, bracket_open = false, bracket_close = false, dot = false, gate = false;
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
                if(punct || digit || bracket_open || bracket_close || dot || gate) {
                    punct = digit = bracket_open = bracket_close = dot = gate = false;
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
                else if(punct || bracket_open || bracket_close || dot || gate) {
                    punct = bracket_open = bracket_close = dot = gate = false;
                    buf[j] = '\0';
                    if(buf[0] != '\0') {assignType(hm, buf);}
                    j = 0;
                }
                if(!alpha && !bracket_open && !bracket_close && !punct && !dot && !gate) {
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
            else if(alpha || bracket_close || bracket_open || punct || digit || gate) {
                alpha = bracket_close = bracket_open = punct = digit = gate = false;
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
                if(alpha || digit || bracket_open || bracket_close || dot || gate) {
                    alpha = digit = bracket_open = bracket_close = dot = gate = false;
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
                if(alpha || digit || punct || bracket_close || dot || gate) {
                    alpha = digit = punct = bracket_close = dot = gate = false;
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
                if(alpha || digit || punct || bracket_open || dot || gate) {
                    alpha = digit = punct = bracket_open = dot = gate = false;
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
            if(c == ',')
                fseek(fp, -1, SEEK_CUR);
        }
        else if(GATE_COND_LEX(c)) {
            while(GATE_COND_LEX(c)) {
                if(alpha || digit || punct || bracket_open || dot || bracket_close) {
                    alpha = digit = punct = bracket_open = dot = bracket_close = false;
                    buf[j] = '\0';
                    if(buf[0] != '\0') {assignType(hm, buf);}
                    j = 0;
                }
                gate = true;
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
                if(alpha || digit || punct || bracket_close || bracket_open || dot || gate) {
                    alpha = digit = punct = bracket_close = bracket_open = dot = gate = false;
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
            else if(c == '\'') {
                if(alpha || digit || punct || bracket_close || bracket_open || dot || gate) {
                    alpha = digit = punct = bracket_close = bracket_open = dot = gate = false;
                    buf[j] = '\0';
                    if(buf[0] != '\0') {assignType(hm, buf);}
                    j = 0;
                }

                buf[j++] = c;
                while((c = fgetc(fp)) != '\'') {
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
                if(alpha || digit || punct || bracket_close || bracket_open || dot || gate) {
                    alpha = digit = punct = bracket_open = bracket_close = dot = gate = false;
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
                alpha = digit = punct = bracket_open = bracket_close = dot = gate = false;
                buf[j++] = c;
                buf[j] = '\0';
                if(buf[0] != '\0') {assignType(hm, buf);}
                j = 0;
            }
		}
	}

    if(alpha || digit || punct || bracket_open || bracket_close || dot || gate) {
        alpha = digit = punct = bracket_open = bracket_close = dot = gate = false;
        buf[j] = '\0';
        if(buf[0] != '\0') {assignType(hm, buf);}
        j = 0;
    }

    j = 0;
    buf[j] = '$';
    buf[j+1] = '\0';
    assignType(hm, buf);

    return hm;
}

#endif