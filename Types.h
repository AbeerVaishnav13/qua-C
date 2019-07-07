#ifndef TYPES_H
#define TYPES_H

typedef enum t {
    // CLASSES
    IDENTIFIER, // function/variable name
    INT_LITERAL, // integer number
    FLOAT_LITERAL, // float number
    STRING_LITERAL, // "surrounded by double quotes"
    CHAR_LITERAL, // surrounded by ' '
    BOOL_LITERAL, // true & false

    // TOKENS
    CMPND_STMT_OPEN, CMPND_STMT_CLOSE, // {.}
    COMMA, /* , */
    ELIF, // elif
    ELSE, // else
    END_OF_LINE, /* ";" */ 
    EXPR_PARANTHESIS_OPEN, EXPR_PARANTHESIS_CLOSE, // (.)
    FOR, // for
    FUNC, //func
    GATE_SEPARATOR, // (H | H)
    IDENTIFIER_DOT, // arr[0].param
    IDX_BRACKET_OPEN, IDX_BRACKET_CLOSE, // [.]
    IF, // if
    IN, // in
    INPUT, // input
    NEW, // new
    PRINT_FORMAT, PRINT, // print, NON_ZERO, ALL
    QUREG, // quReg
    QUBIT, // quBit
    RANGE, // (2...10)
    RETURN, // return
    SAVE, // save
    VAR, VAL, INT, CHAR, BOOL, VOID, FLOAT, STRING,// Int, Char, Bool, Void, Float, String
    WHILE, //while

    // OPERATORS
    APPLY_GATES, // (->)
    INC, DEC, NEG, BIT_AND, BIT_OR, BIT_EXOR, BIT_INV, // Unary operators
    ADD, SUB, MULT, DIV, ASSIGN/* = */, EQUALS, N_EQUALS, GT, LT, GTET, LTET, AND, OR, ADD_ASSIGN, SUB_ASSIGN, // Binary Operators
    IF_THEN_ELSE, // Ternary Operator
    EXPLICIT_TYPE_ASSIGN, // Explicit datatype assignment
    TX_TO_FUNC, // (<-)
    RX_FROM_FUNC, // (=>)

    // GATES
    CNOT_o, // Co
    CNOT_x, // Cx
    HADAMARD, // H
    INV_QFT, // Qi
    NOOP, // ~
    PAULI_X, // X
    PAULI_Y, // Y
    PAULI_Z, // Z
    PHASE, // S
    QFT, // Q
    ROTATION, // R_xx.xx
    SWAP, // Sx

    CLASS, // class keyword
    INHERITS, // inheritance using 'from'
    ACCESS_SPEC, // For access specifiers
    STATIC // static keyword
}Type;

char Types_str[83][23] = {
    // DATA CLASSES
    "IDENTIFIER", // function/variable name
    "INT_LITERAL", // integer number
    "FLOAT_LITERAL", // float number
    "STRING_LITERAL", // "surrounded by double quotes"
    "CHAR_LITERAL", // surrounded by ' '
    "BOOL_LITERAL", // true & false

    // TOKENS
    "CMPND_STMT_OPEN", "CMPND_STMT_CLOSE", // {.}
    "COMMA", /* , */
    "ELIF", // elif
    "ELSE", // else
    "END_OF_LINE", /* ";" */ 
    "EXPR_PARANTHESIS_OPEN", "EXPR_PARANTHESIS_CLOSE", // (.)
    "FOR", // for
    "FUNC", //func
    "GATE_SEPARATOR", // (H | H)
    "IDENTIFIER_DOT", // arr[0].param
    "IDX_BRACKET_OPEN", "IDX_BRACKET_CLOSE", // [.]
    "IF", // if
    "IN", // in
    "INPUT", // input
    "NEW", // new
    "PRINT_FORMAT", "PRINT", // print, NON_ZERO, ALL
    "QUREG", // quReg
    "QUBIT", // quBit
    "RANGE", // (2...10)
    "RETURN", // return
    "SAVE", // save
    "VAR", "VAL", "INT", "CHAR", "BOOL", "VOID", "FLOAT", "STRING",// Int, Char, Bool, Void, Float, String
    "WHILE", //while

    // OPERATORS
    "APPLY_GATES", // (->)
    "INC", "DEC", "NEG", "BIT_AND", "BIT_OR", "BIT_EXOR", "BIT_INV", // Unary operators
    "ADD", "SUB", "MULT", "DIV", "ASSIGN", /* <- */ "EQUALS", "N_EQUALS", "GT", "LT", "GTET", "LTET", "AND", "OR", "ADD_ASSIGN", "SUB_ASSIGN", // Binary Operators
    "IF_THEN_ELSE", // Ternary Operator
    "EXPLICIT_TYPE_ASSIGN", // Explicit datatype assignment
    "TX_TO_FUNC", // (<=)
    "RX_FROM_FUNC", // (=>)

    // GATES
    "CNOT_o", // Co
    "CNOT_x", // Cx
    "HADAMARD", // H
    "INV_QFT", // Qi
    "NOOP", // ~
    "PAULI_X", // X
    "PAULI_Y", // Y
    "PAULI_Z", // Z
    "PHASE", // S
    "QFT", // Q
    "ROTATION", // R_xx.xx
    "SWAP", // Sx

    "CLASS", // class keyword
    "INHERITS", // inheritance using 'from'
    "ACCESS_SPEC", // For access specifiers
    "STATIC" // static keyword
};

#endif