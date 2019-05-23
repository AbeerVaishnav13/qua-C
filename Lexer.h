#ifndef LEXER_H
#define LEXER_H

#define BRACKET_CONDITION_OPEN(c) (c == '(' || c == '[' || c == '{')
#define BRACKET_CONDITION_CLOSE(c) (c == ')' || c == ']' || c == '}')

#define PUNCTUATION_CONDITION(c) (c == '=' || c == '<' || c == '>' || c == ',' || \
                                    c == '-' || c == ':' || c == '.' || c == '|')

void assignType(HashMap *hm, char buf[]) {
    if(!strcmp(buf, "{")) {insertHM(hm, buf, CMPND_STMT_OPEN);}
    else if(!strcmp(buf, "{")) {insertHM(hm, buf, CMPND_STMT_OPEN);}
    else if(!strcmp(buf, "}")) {insertHM(hm, buf, CMPND_STMT_CLOSE);}
    else if(!strcmp(buf, "[")) {insertHM(hm, buf, IDX_BRACKET_OPEN);}
    else if(!strcmp(buf, "]")) {insertHM(hm, buf, IDX_BRACKET_CLOSE);}
    else if(!strcmp(buf, "(")) {insertHM(hm, buf, EXPR_PARANTHESIS_OPEN);}
    else if(!strcmp(buf, ")")) {insertHM(hm, buf, EXPR_PARANTHESIS_CLOSE);}
    else if(!strcmp(buf, ",")) {insertHM(hm, buf, COMMA);}
    else if(!strcmp(buf, "::")) {insertHM(hm, buf, COLON_COLON);}
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
    else if(!strcmp(buf, "quReg")) {insertHM(hm, buf, QUREG);}
    else if(!strcmp(buf, "quBit")) {insertHM(hm, buf, QUBIT);}
    else if(!strcmp(buf, "...")) {insertHM(hm, buf, RANGE);}
    else if(!strcmp(buf, "real")) {insertHM(hm, buf, REAL);}
    else if(!strcmp(buf, "imag")) {insertHM(hm, buf, IMAG);}
    else if(!strcmp(buf, "return")) {insertHM(hm, buf, RETURN);}
    else if(!strcmp(buf, "save")) {insertHM(hm, buf, SAVE);}
    else if(!strcmp(buf, "Int")) {insertHM(hm, buf, INT);}
    else if(!strcmp(buf, "Char")) {insertHM(hm, buf, CHAR);}
    else if(!strcmp(buf, "Bool")) {insertHM(hm, buf, BOOL);}
    else if(!strcmp(buf, "Void")) {insertHM(hm, buf, VOID);}
    else if(!strcmp(buf, "while")) {insertHM(hm, buf, WHILE);}
    else if(!strcmp(buf, "->")) {insertHM(hm, buf, APPLY_GATES);}
    else if(!strcmp(buf, "++")) {insertHM(hm, buf, INC);}
    else if(!strcmp(buf, "--")) {insertHM(hm, buf, DEC);}
    else if(!strcmp(buf, "&")) {insertHM(hm, buf, BIT_AND);}
    else if(!strcmp(buf, "^")) {insertHM(hm, buf, BIT_EXOR);}
    else if(!strcmp(buf, "+")) {insertHM(hm, buf, ADD);}
    else if(!strcmp(buf, "-")) {insertHM(hm, buf, SUB);}
    else if(!strcmp(buf, "*")) {insertHM(hm, buf, MULT);}
    else if(!strcmp(buf, "/")) {insertHM(hm, buf, DIV);}
    else if(!strcmp(buf, "<-")) {insertHM(hm, buf, ASSIGN);}
    else if(!strcmp(buf, "==")) {insertHM(hm, buf, EQUALS);}
    else if(!strcmp(buf, ">")) {insertHM(hm, buf, GT);}
    else if(!strcmp(buf, "<")) {insertHM(hm, buf, LT);}
    else if(!strcmp(buf, ">=")) {insertHM(hm, buf, GTET);}
    else if(!strcmp(buf, "&&")) {insertHM(hm, buf, AND);}
    else if(!strcmp(buf, "||")) {insertHM(hm, buf, OR);}
    else if(!strcmp(buf, "+=")) {insertHM(hm, buf, ADD_ASSIGN);}
    else if(!strcmp(buf, "-=")) {insertHM(hm, buf, SUB_ASSIGN);}
    else if(!strcmp(buf, "?")) {insertHM(hm, buf, IF_THEN_ELSE);}
    else if(!strcmp(buf, ":")) {insertHM(hm, buf, IF_THEN_ELSE);}
    else if(!strcmp(buf, "<=")) {insertHM(hm, buf, TX_TO_FUNC);}
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
    else if(isdigit(buf[0])) {insertHM(hm, buf, INT_LITERAL);}
    else if(buf[0] == '"') {insertHM(hm, buf, STRING_LITERAL);}
    else {insertHM(hm, buf, IDENTIFIER);}
}

HashMap* scanFile(FILE *fp) {
	bool alpha = false, digit = false, punct = false, bracket_open = false, bracket_close = false;
    bool range = false;
	char buf[80];
	int j = 0;
    char c;

    HashMap *hm = newHashMap();

    while((c = fgetc(fp)) != EOF) {
        if(c == '#') {
            while((c = fgetc(fp)) != '\n');
            c = fgetc(fp);
        }
		if(isalpha(c) || c == '_') {
            // printf("Entered alpha\n");
            while(isalpha(c) || c == '_') {
                if(punct || digit || bracket_open || bracket_close) {
                    punct = digit = bracket_open = bracket_close = false;
                    buf[j] = '\0';
                    if(buf[0] != '\0') {assignType(hm, buf);}
                    // printf("%s : %s\n", hm->kt[hm->len-1].key, Types_str[hm->kt[hm->len-1].type]);
                    j = 0;
                }
                alpha = true;
                buf[j++] = c;
                // printf("\talpha: %s\n", buf);

                c = fgetc(fp);
            }
            fseek(fp, -1, SEEK_CUR);
		}
		else if(isdigit(c)) {
            // printf("Entered digit\n");
            while(isdigit(c)) {
                if(alpha) {
                    buf[j++] = c;
                }
                else if(punct || bracket_open || bracket_close) {
                    punct = bracket_open = bracket_close = false;
                    buf[j] = '\0';
                    if(buf[0] != '\0') {assignType(hm, buf);}
                    // printf("%s : %s\n", hm->kt[hm->len-1].key, Types_str[hm->kt[hm->len-1].type]);
                    j = 0;
                }
                if(!alpha && !bracket_open && !bracket_close && !punct) {
                    digit = true;
                    buf[j++] = c;
                }
                // printf("\tdigit: %s\n", buf);

                c = fgetc(fp);
            }
            fseek(fp, -1, SEEK_CUR);
		}
		else if(PUNCTUATION_CONDITION(c)) {
            char ch = fgetc(fp);
            fseek(fp, -1, SEEK_CUR);
            // printf("Entered punct\n");
            while(PUNCTUATION_CONDITION(c)) {
                // printf("buf[j-1] = %c\n", buf[j-1]);
                if(buf[0] == 'R' && buf[1] == '_') {
                    buf[j++] = c;
                }
                else if(alpha || digit || bracket_open || bracket_close) {
                    alpha = digit = bracket_open = bracket_close = false;
                    buf[j] = '\0';
                    if(buf[0] != '\0') {assignType(hm, buf);}
                    // printf("%s : %s\n", hm->kt[hm->len-1].key, Types_str[hm->kt[hm->len-1].type]);
                    j = 0;
                }
                else {
                    punct = true;
                    buf[j++] = c;
                }
                // printf("\tpunct: %s\n", buf);

                c = fgetc(fp);
            }
            fseek(fp, -1, SEEK_CUR);
		}
        else if(BRACKET_CONDITION_OPEN(c)) {
            // printf("Entered bracket\n");
            while (BRACKET_CONDITION_OPEN(c)) {
                if(alpha || digit || punct || bracket_close) {
                    alpha = digit = punct = bracket_close = false;
                    buf[j] = '\0';
                    if(buf[0] != '\0') {assignType(hm, buf);}
                    // printf("%s : %s\n", hm->kt[hm->len-1].key, Types_str[hm->kt[hm->len-1].type]);
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
                // printf("\tbracket: %s\n", buf);

                c = fgetc(fp);
            }
            fseek(fp, -1, SEEK_CUR);
        }
        else if(BRACKET_CONDITION_CLOSE(c)) {
            // printf("Entered bracket\n");
            while (BRACKET_CONDITION_CLOSE(c)) {
                if(alpha || digit || punct || bracket_open) {
                    alpha = digit = punct = bracket_open = false;
                    buf[j] = '\0';
                    if(buf[0] != '\0') {assignType(hm, buf);}
                    // printf("%s : %s\n", hm->kt[hm->len-1].key, Types_str[hm->kt[hm->len-1].type]);
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
                // printf("\tbracket: %s\n", buf);

                c = fgetc(fp);
            }
            fseek(fp, -1, SEEK_CUR);
        }
        else if(c == '"') {
            if(alpha || digit || punct || bracket_close || bracket_open) {
                alpha = digit = punct = bracket_close = bracket_open = false;
                buf[j] = '\0';
                if(buf[0] != '\0') {assignType(hm, buf);}
                // printf("%s : %s\n", hm->kt[hm->len-1].key, Types_str[hm->kt[hm->len-1].type]);
                j = 0;
            }
            buf[j++] = c;
            while((c = fgetc(fp)) != '"') {
                buf[j++] = c;
            }
            buf[j] = c;
            buf[j+1] = '\0';
            if(buf[0] != '\0') {assignType(hm, buf);}
            // printf("%s : %s\n", hm->kt[hm->len-1].key, Types_str[hm->kt[hm->len-1].type]);
            j = 0;
        }
		else if(c == ' ' || c == '\n' || c == '\t') {
            // printf("Entered space\n");
            while(c == ' ' || c == '\n' || c == '\t') {
                alpha = digit = punct = bracket_open = bracket_close = false;
                buf[j] = '\0';
                if(buf[0] != '\0') {assignType(hm, buf);}
                // printf("%s : %s\n", hm->kt[hm->len-1].key, Types_str[hm->kt[hm->len-1].type]);
                j = 0;
                // printf("\tspace: %s\n", buf);

                c = fgetc(fp);
            }
            char ch;
            if((ch = fgetc(fp)) != EOF) {
            	fseek(fp, -2, SEEK_CUR);
            }
		}
	}

    return hm;
}

#endif