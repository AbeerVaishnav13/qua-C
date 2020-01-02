#ifndef TYPES_H
#define TYPES_H

typedef enum t {
    // CLASSES
    IDENTIFIER, // function/variable name
    INT_LITERAL, // integer number
    FLOAT_LITERAL, // float number
    STRING_LITERAL, // surrounded by double quotes or single quotes -> "" or ''

    // TOKENS
    CMPND_STMT_OPEN, CMPND_STMT_CLOSE, // {.}
    COMMA, /* , */
    EXPR_PARANTHESIS_OPEN, EXPR_PARANTHESIS_CLOSE, // (.)
    FUNC, //func
    GATE, //gate
    DOT, // arr[0].param
    IDX_BRACKET_OPEN, IDX_BRACKET_CLOSE, // [.]
    NEW, // new
    PRINT, // print, NON_ZERO, ALL
    QUREG, // quReg
    MATH_PI, // PI constant (π)
    DIVISION, // (/)
    MULTIPLICATION, // (*)

    // OPERATORS
    REG_NAME, // (=>)
    EQUALS, // (=)

    // GATES
    PAULI_X, // X
    PAULI_Y, // Y
    PAULI_Z, // Z
    PHASE, // S
    ROTATION_X, // Rx
    ROTATION_Y, // Ry
    ROTATION_Z, // Rz
    HADAMARD, // H
    SWAP, // x
    QFT, // ~
    CONTROL, // @
    INV_CONTROL, // o
    POWER, // ^
    IDENTITY, // -

    LIST_END
}Type;

char Types_str[37][23] = {
    // CLASSES
    "IDENTIFIER", // function/variable name
    "INT_LITERAL", // integer number
    "FLOAT_LITERAL", // float number
    "STRING_LITERAL", // surrounded by double quotes or single quotes -> "" or ''

    // TOKENS
    "CMPND_STMT_OPEN", "CMPND_STMT_CLOSE", // {.}
    "COMMA", /* , */
    "EXPR_PARANTHESIS_OPEN", "EXPR_PARANTHESIS_CLOSE", // (.)
    "FUNC", //func
    "GATE", //gate
    "DOT", // arr[0].param
    "IDX_BRACKET_OPEN", "IDX_BRACKET_CLOSE", // [.]
    "NEW", // new
    "PRINT", // print statement
    "QUREG", // quReg
    "MATH_PI", // PI constant (π)
    "DIVISION", // (/)
    "MULTIPLICATION", // (*)

    // OPERATORS
    "REG_NAME", // (=>)
    "EQUALS", // (=)

    // GATES
    "PAULI_X", // X
    "PAULI_Y", // Y
    "PAULI_Z", // Z
    "PHASE", // S
    "ROTATION_X", // Rx
    "ROTATION_Y", // Ry
    "ROTATION_Z", // Rz
    "HADAMARD", // H
    "SWAP", // x
    "QFT", // ~
    "CONTROL", // @
    "INV_CONTROL", // o
    "POWER", // ^
    "IDENTITY", // -

    "LIST_END",
};

#endif