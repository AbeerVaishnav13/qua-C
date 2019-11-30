#ifndef QUANTUM_PARSER_H
#define QUANTUM_PARSER_H

#define GATE_COND_PARSE(c) (c == PAULI_X || c == PAULI_Y || c == PAULI_Z || c == HADAMARD || \
                      c == ROTATION || c == SWAP || c == QFT || c == CONTROL || c == INV_CONTROL || \
                      c == POWER || c == X_AXIS_CONTROL || c == Y_AXIS_CONTROL || c == IDENTITY || \
                      c == PHASE || c == IDENTIFIER)

/*
////////////////////////////////////////
SAMPLE PROGRAM
////////////////////////////////////////

gate Uw[6] {
    [-, -, -, X, -, -]
    [X, @, @, @, @, @]
    [-, -, -, X, -, -]
}

gate Us[6] {
    [-, H, H, H, H, H]
    [-, X, X, X, X, X]
    [X, @, @, @, @, @]
    [-, X, X, X, X, X]
    [-, H, H, H, H, H]
}

func grover {
    [X, -, -, -, -, -]
    [H, H, H, H, H, H]
    [Uw]
    [Us]
    [Uw]
    [Us]
    [Uw]
    [Us]
    [Uw]
    [Us]
    Pa()
}

quReg qr = new quReg[6] => 'qr1'
qr.setPrecision(6)

qr.Pnz()
qr.grover()
qr.Pnz()

////////////////////////////////////////
CONTEXT FREE GRAMMER !!! (CFG)
////////////////////////////////////////

P -> F N D P | G N QA D P | I                                                           DONE
F -> func                                                                               DONE
G -> gate                                                                               DONE
QA -> [ num ]                                                                           DONE
N -> alnum                                                                              DONE
D -> { C }                                                                              DONE
C -> [ Gate ] C | PRINT_COND C | e                                                      DONE
Gate -> GATE_COND , Gate | GATE_COND (FLOAT_LITERAL), Gate | GATE_COND                          DONE

I -> Q N E Exp NL                                                                       DONE
Exp -> New Q Size Name | alnum | String                                                 DONE
Q -> quReg                                                                              DONE
New -> new                                                                              DONE
E -> =                                                                                  DONE
Size -> [ alnum ]                                                                       DONE
Name -> => String | e                                                                   DONE
String -> ' chars ' | " chars " | ' ' | " "                                             DONE

NL -> N Dot Param NL | I | e                                                            DONE
Dot -> .                                                                                DONE
Param -> N Paranthesis | PRINT_COND                                                     DONE
Paranthesis -> ( ) | ( alnum ) | e                                                      DONE


////////////////////////////////////////
CONTEXT FREE GRAMMER !!! (CFG) (with Types.h)
////////////////////////////////////////

P -> F N D P | G N QA D P | I
F -> FUNC
G -> GATE
QA -> IDX_BRACKET_OPEN (IDENTIFIER or INT_LITERAL) IDX_BRACKET_CLOSE
N -> IDENTIFIER
D -> CMPND_STMT_OPEN C CMPND_STMT_CLOSE
C -> IDX_BRACKET_OPEN G IDX_BRACKET_CLOSE C | PRINT_COND C | e
Gate -> GATE_COND COMMA Gate | GATE_COND EXPR_PARANTHESIS_OPEN FLOAT_LITERAL EXPR_PARANTHESIS_OPEN COMMA Gate | GATE_COND

I -> Q N E Exp NL
Exp -> New Q Size Name | IDENTIFIER | STRING_LITERAL
Q -> QUREG
New -> NEW
E -> EQUALS
Size -> IDX_BRACKET_OPEN (IDENTIFIER or INT_LITERAL) IDX_BRACKET_CLOSE
Name -> REG_NAME STRING_LITERAL | e

NL -> N Dot Param NL | I | e
Dot -> DOT
Param -> N Paranthesis | PRINT_COND
Paranthesis -> EXPR_PARANTHESIS_OPEN EXPR_PARANTHESIS_CLOSE | EXPR_PARANTHESIS_OPEN (IDENTIFIER or INT_LITERAL) EXPR_PARANTHESIS_CLOSE | e
*/
 
int error, i = 0;
Type *input;

bool Parse(); // Program
void F(); // func
void G(); // gate
void QA(); // qubit array
void N(); // Name
void D(); // Description
void C(); // Columns
void Gate(); // Gates

void I(); // Init_simulation
void Exp(); // Expression
void Q(); // quReg
void New(); // new
void E(); // Equal-to
void Size(); // qureg size
void Name(); // qureg name
void String(); // parse any string

void NL(); // next line
void Dot(); // a dot
void Param(); // specifying a param for qr
void Paranthesis(); // For giving paranthesis

// P -> F N D P | G N QA D P | I
bool Parse() { // Program
    if(input[i] == LIST_END)
        return true;

    if(input[i] == FUNC) {
        F();
        N();
        D();
        Parse();
    }
    else if(input[i] == GATE) {
        G();
        N();
        QA();
        D();
        Parse();
    }
    else if(input[i] == QUREG) {
        I();
    }
    else {
        error = -1;
        printf("[!] Incorrect syntax. [%d]\n", error);
    }

    return (error == 0 ? true : false);
}

// F -> func
void F() { // func
    if(input[i] == FUNC) {
        i++;
    }
    else {
        error = -2;
        printf("[!] Encountered something else instead of 'func'. [%d]\n", error);
    }
}

// G -> gate
void G() { // gate
    if(input[i] == GATE) {
        i++;
    }
    else {
        error = -3;
        printf("[!] Encountered something else instead of 'gate'. [%d]\n", error);
    }
}

// QA -> [num]
void QA() {
    if(input[i] == IDX_BRACKET_OPEN) {
        i++;
        if(input[i] == INT_LITERAL) {
            i++;
            if(input[i] == IDX_BRACKET_CLOSE)
                i++;
            else {
                error = -4;
                printf("[!] Closing bracket ']' missing. [%d]\n", error);
            }
        }
        else {
            error = -5;
            printf("[!] A numerical value expected within square brackets. [%d]\n", error);
        }
    }
    else {
        error = -6;
        printf("[!] A parameter should be specified after gate identifier within [.] to specify the number of qubits to which the gate has to be applied. [%d]\n", error);
    }
}

// N -> alnum
void N() { // Name
    if(input[i] == IDENTIFIER)
        i++;
    else {
        error = -7;
        printf("[!] Found: '%c' instead of alnum data. [%d]\n", input[i], error);
    }
}

// D -> {C}
void D() { // Description
    if(input[i] == CMPND_STMT_OPEN) {
        i++;
        C();
        if(input[i] == CMPND_STMT_CLOSE)
            i++;
        else {
            error = -8;
            printf("[!] Closing bracket '}' missing. [%d]\n", error);
        }
    }
    else {
        error = -9;
        printf("[!] Opening bracket '{' missing. [%d]\n", error);
    }
}

// C -> [G]C | Pa()C | Pnz()C | e
void C() { // Columns
    if(input[i] == IDX_BRACKET_OPEN) {
        i++;
        Gate();
        if(input[i] == IDX_BRACKET_CLOSE) {
            i++;
            C();
        }
        else {
            error = -10;
            printf("[!] Closing bracket ']' missing. [%d]\n", error);
        }
    }
    else if(input[i] == PRINT) {
        i++;
        if(input[i] == EXPR_PARANTHESIS_OPEN && input[i+1] == EXPR_PARANTHESIS_CLOSE)
            i += 2;
        else {
            error = -11;
            printf("[!] Expected '()' after print statement. [%d]\n", error);
        }
        C();
    }
    else {
        if(input[i] == CMPND_STMT_CLOSE)
            return;
        else {
            error = -12;
            printf("[!] Opening bracket '[' missing. [%d]\n", error);
        }
    }
}

// Gate -> alnum , Gate| alnum
void Gate() { // Gates
    if(GATE_COND_PARSE(input[i])) {
        bool found_other_gate = false;

        if(input[i] == SWAP) {
            i++;
            while(input[i] != SWAP) {
                if(!(input[i] == COMMA || input[i] == IDENTITY)) {
                    found_other_gate = true;
                }
                i++;
                if(input[i] == IDX_BRACKET_CLOSE)
                    break;
            }
            if(found_other_gate) {
                error = -27;
                printf("[!] Cannot use any ther gate except IDENTITY gate between two SWAP gates. [%d]\n", error);
            }
            if(input[i] == IDX_BRACKET_CLOSE) {
                error = -28;
                printf("[!] SWAP gates should be used in pair. Cannot find two SWAP gates in the same row. [%d]\n", error);
                i--;
            }
            else
                i++;
        }
        else
            i++;

        if(input[i] == EXPR_PARANTHESIS_OPEN) {
            i++;
            if(input[i] == FLOAT_LITERAL || input[i] == INT_LITERAL) {
                i++;
                if(input[i] == EXPR_PARANTHESIS_CLOSE) {
                    i++;
                    if(input[i] == COMMA) {
                        i++;
                        Gate();
                    }
                    else
                        return;
                }
                else {
                    error = -30;
                    printf("[!] Expected a closing paranthesis. [%d]\n", error);
                }
            }
            else {
                error = -29;
                printf("[!] Expected a float ot integer literal within the paranthesis. [%d]\n", error);
            }
        }

        if(input[i] == COMMA) {
            i++;
            Gate();
        }
        else
            return;
    }
    else {
        error = -13;
        printf("[!] Invalid gate at '%c'. [%d]\n", input[i], error);
    }
}

// I -> Q N E Exp NL
void I() { // Init_simulation
    Q();
    N();
    E();
    Exp();
    NL();
}

// Exp -> New Q Size Name | alnum | String
void Exp() { // Expression
    if(input[i] == NEW) {
        New();
        Q();
        Size();
        Name();
    }
    else if(input[i] == IDENTIFIER) {
        i++;
    }
    else if(input[i] == STRING_LITERAL)
        i++;
    else {
        error = -14;
        printf("[!] Invalid expression. Please check the syntax. [%d]\n", error);
    }
}

// Q -> quReg
void Q() { // quReg
    if(input[i] == QUREG)
        i++;
    else {
        error = -15;
        printf("[!] Invalid datatype. [%d]\n", error);
    }
}

// New -> new
void New() { // new
    if(input[i] == NEW)
        i++;
    else {
        error = -16;
        printf("[!] Encountered something else instead of 'new'. [%d]\n", error);
    }
}

// E -> =
void E() { // Equal-to
    if(input[i] == EQUALS)
        i++;
    else {
        error = -17;
        printf("[!] Encountered something else instead of '='. [%d]\n", error);
    }
}

// Size -> [alnum]
void Size() { // qureg size
    if(input[i] == IDX_BRACKET_OPEN) {
        i++;
        if(input[i] == IDENTIFIER || input[i] == INT_LITERAL) {
            i++;
            if(input[i] == IDX_BRACKET_CLOSE)
                i++;
            else {
                error = -18;
                printf("[!] Closing bracket ']' missing. [%d]\n", error);
            }
        }
        else {
            error = -19;
            printf("[!] Expected an integer or variable identifier. [%d]\n", error);
        }
    }
    else {
        error = -20;
        printf("[!] Opening bracket '[' missing. [%d]\n", error);
    }
}

// Name -> => String | e
void Name() { // qureg name
    if(input[i] == REG_NAME) {
        i++;
        if(input[i] == STRING_LITERAL)
            i++;
        else {
            error = -21;
            printf("[!] Expected a name for the quRegister within '' or \"\". [%d]\n", error);
        }
    }
}

// NL -> N Dot Param NL | I | e
void NL() { // next line
    if(input[i] == LIST_END)
        return;

    if(input[i] == QUREG) {
        I();
    }
    else if(input[i] == IDENTIFIER) {
        N();
        Dot();
        Param();
        NL();
    }
    else {
        error = -22;
        printf("[!] Incorrect syntax. Expected a datatype or variable identifier. [%d]\n", error);
    }
}

// Dot -> .
void Dot() { // a dot
    if(input[i] == DOT && input[i-1] == IDENTIFIER)
        i++;
    else {
        error = -23;
        printf("[!] Expected an identifier before dot operator. [%d]\n", error);
    }
}

// Param -> N Paranthesis | Pa() | Pnz()
void Param() { // specifying a param for qr
    if(input[i] == PRINT) {
        i++;
        if(input[i] == EXPR_PARANTHESIS_OPEN && input[i+1] == EXPR_PARANTHESIS_CLOSE)
            i += 2;
        else {
            error = -24;
            printf("[!] Expected '()' after print statement. [%d]\n", error);
        }
    }
    else if(input[i] == IDENTIFIER) {
        N();
        Paranthesis();
    }
    else {
        error = -25;
        printf("[!] Incorrect syntax. Expected a variable/function identifier. [%d]\n", error);
    }
}

// Paranthesis -> () | (alnum) | e
void Paranthesis() { // For giving paranthesis
    if(input[i] == EXPR_PARANTHESIS_OPEN) {
        i++;
        if(input[i] == IDENTIFIER || input[i] == INT_LITERAL || input[i] == FLOAT_LITERAL)
            i++;

        if(input[i] == EXPR_PARANTHESIS_CLOSE)
            i++;
        else {
            error = -26;
            printf("[!] Closing bracket ')' missing. [%d]\n", error);
        }  
    }
}

#endif