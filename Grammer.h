#ifndef GRAMMER_H
#define GRAMMER_H

#define NUM_PRODUCTIONS 90

#define ONE_PRODUCTION 25
#define TWO_PRODUCTION (ONE_PRODUCTION + 12)
#define THREE_PRODUCTION (TWO_PRODUCTION + 33)
#define FOUR_PRODUCTION (THREE_PRODUCTION + 3)
#define FIVE_PRODUCTION (FOUR_PRODUCTION + 11)
#define EIGHT_PRODUCTION (FIVE_PRODUCTION + 1)
#define NINE_PRODUCTION (EIGHT_PRODUCTION + 2)

typedef enum v {
    library = 74,
    functions,
    paramdecls,
    paramdecl,
    stmt,
    com_stmt,
    vardefs,
    vardef_single,
    vardef_array,
    print,
    save,
    dataType,
    expr,
    expr_quantum
}Variables;

char Var_str[14][14] = {
    "library",
    "functions",
    "paramdecls",
    "paramdecl",
    "stmt",
    "com_stmt",
    "vardefs",
    "vardef_single",
    "vardef_array",
    "print",
    "save",
    "dataType",
    "expr",
    "expr_quantum"
};

typedef struct p {
    int alpha;
    int *beta;
}Production;

int* makeBeta(int len, int arr[]) {
	int *Arr = (int*) malloc(len * sizeof(int));
	for(int i = 0; i < len; i++) {
		Arr[i] = arr[i];
	}
	return Arr;
}

// Production newProduction(int alpha, int beta[], int beta_size) {
//     Production prod;
//     prod.alpha = alpha;
//     prod.beta = (int*) malloc(beta_size * sizeof(int));
//     int i;
//     for(i = 0; i < beta_size; i++) {
//         prod.beta[i] = beta[i];
//     }

//     return prod;
// }

void initProductions(Production *prod) {
    Production p[87] = {
        [0].alpha = paramdecls,     [0].beta = makeBeta(1, (int[]){paramdecl}),
        [1].alpha = stmt,           [1].beta = makeBeta(1, (int[]){END_OF_LINE}),
        [2].alpha = com_stmt,       [2].beta = makeBeta(1, (int[]){CMPND_STMT_OPEN}),
        [3].alpha = dataType,       [3].beta = makeBeta(1, (int[]){INT}),
        [4].alpha = dataType,       [4].beta = makeBeta(1, (int[]){CHAR}),
        [5].alpha = dataType,       [5].beta = makeBeta(1, (int[]){BOOL}),
        [6].alpha = dataType,       [6].beta = makeBeta(1, (int[]){FLOAT}),
        [7].alpha = dataType,       [7].beta = makeBeta(1, (int[]){VOID}),
        [8].alpha = dataType,       [8].beta = makeBeta(1, (int[]){QUREG}),
        [9].alpha = dataType,       [9].beta = makeBeta(1, (int[]){QUBIT}),
        [10].alpha = expr,          [10].beta = makeBeta(1, (int[]){INT_LITERAL}),
        [11].alpha = expr,          [11].beta = makeBeta(1, (int[]){FLOAT_LITERAL}),
        [12].alpha = expr,          [12].beta = makeBeta(1, (int[]){STRING_LITERAL}),
        [13].alpha = expr_quantum,  [13].beta = makeBeta(1, (int[]){HADAMARD}),
        [14].alpha = expr_quantum,  [14].beta = makeBeta(1, (int[]){PHASE}),
        [15].alpha = expr_quantum,  [15].beta = makeBeta(1, (int[]){ROTATION}),
        [16].alpha = expr_quantum,  [16].beta = makeBeta(1, (int[]){PAULI_X}),
        [17].alpha = expr_quantum,  [17].beta = makeBeta(1, (int[]){PAULI_Y}),
        [18].alpha = expr_quantum,  [18].beta = makeBeta(1, (int[]){PAULI_Z}),
        [19].alpha = expr_quantum,  [19].beta = makeBeta(1, (int[]){QFT}),
        [20].alpha = expr_quantum,  [20].beta = makeBeta(1, (int[]){INV_QFT}),
        [21].alpha = expr_quantum,  [21].beta = makeBeta(1, (int[]){CNOT_o}),
        [22].alpha = expr_quantum,  [22].beta = makeBeta(1, (int[]){CNOT_x}),
        [23].alpha = expr_quantum,  [23].beta = makeBeta(1, (int[]){SWAP}),
        [24].alpha = expr_quantum,  [24].beta = makeBeta(1, (int[]){NOOP}),

        [25].alpha = functions,     [25].beta = makeBeta(2, (int[]){functions, functions}),
        [26].alpha = stmt,          [26].beta = makeBeta(2, (int[]){com_stmt, CMPND_STMT_CLOSE}),
        [27].alpha = stmt,          [27].beta = makeBeta(2, (int[]){ELSE, stmt}),
        [28].alpha = stmt,          [28].beta = makeBeta(2, (int[]){vardefs, END_OF_LINE}),
        [29].alpha = stmt,          [29].beta = makeBeta(2, (int[]){expr, END_OF_LINE}),
        [30].alpha = com_stmt,      [30].beta = makeBeta(2, (int[]){com_stmt, stmt}),
        [31].alpha = vardefs,       [31].beta = makeBeta(2, (int[]){dataType, vardef_single}),
        [32].alpha = vardefs,       [32].beta = makeBeta(2, (int[]){dataType, vardef_array}),
        [33].alpha = expr,          [33].beta = makeBeta(2, (int[]){INC, expr}),
        [34].alpha = expr,          [34].beta = makeBeta(2, (int[]){DEC, expr}),
        [35].alpha = expr,          [35].beta = makeBeta(2, (int[]){expr, INC}),
        [36].alpha = expr,          [36].beta = makeBeta(2, (int[]){expr, DEC}),
        
        [37].alpha = paramdecl,     [37].beta = makeBeta(3, (int[]){IDENTIFIER, COLON_COLON, dataType}),
        [38].alpha = stmt,          [38].beta = makeBeta(3, (int[]){RETURN, expr, END_OF_LINE}),
        [39].alpha = stmt,          [39].beta = makeBeta(3, (int[]){PRINT, print, END_OF_LINE}),
        [40].alpha = stmt,          [40].beta = makeBeta(3, (int[]){SAVE, save, END_OF_LINE}),
        [41].alpha = vardefs,       [41].beta = makeBeta(3, (int[]){vardefs, COMMA, vardef_single}),
        [42].alpha = vardef_single, [42].beta = makeBeta(3, (int[]){IDENTIFIER, ASSIGN, expr}),
        [43].alpha = vardef_array,  [43].beta = makeBeta(3, (int[]){IDENTIFIER, IDX_BRACKET_OPEN, IDX_BRACKET_CLOSE}),
        [44].alpha = print,         [44].beta = makeBeta(3, (int[]){COLON_COLON, PRINT_FORMAT, print}),
        [45].alpha = save,          [45].beta = makeBeta(3, (int[]){COLON_COLON, PRINT_FORMAT, save}),
        [46].alpha = expr,          [46].beta = makeBeta(3, (int[]){EXPR_PARANTHESIS_OPEN, expr, EXPR_PARANTHESIS_CLOSE}),
        [47].alpha = expr,          [47].beta = makeBeta(3, (int[]){IDX_BRACKET_OPEN, expr, IDX_BRACKET_CLOSE}),
        [48].alpha = expr,          [48].beta = makeBeta(3, (int[]){expr, EXPR_PARANTHESIS_OPEN,  EXPR_PARANTHESIS_CLOSE}),
        [49].alpha = expr,          [49].beta = makeBeta(3, (int[]){expr, ASSIGN, expr}),
        [50].alpha = expr,          [50].beta = makeBeta(3, (int[]){expr, ASSIGN, stmt}),
        [51].alpha = expr,          [51].beta = makeBeta(3, (int[]){expr, ADD, expr}),
        [52].alpha = expr,          [52].beta = makeBeta(3, (int[]){expr, SUB, expr}),
        [53].alpha = expr,          [53].beta = makeBeta(3, (int[]){expr, MULT, expr}),
        [54].alpha = expr,          [54].beta = makeBeta(3, (int[]){expr, DIV, expr}),
        [55].alpha = expr,          [55].beta = makeBeta(3, (int[]){expr, GT, expr}),
        [56].alpha = expr,          [56].beta = makeBeta(3, (int[]){expr, LT, expr}),
        [57].alpha = expr,          [57].beta = makeBeta(3, (int[]){expr, GTET, expr}),
        [58].alpha = expr,          [58].beta = makeBeta(3, (int[]){expr, LTET, expr}),
        [59].alpha = expr,          [59].beta = makeBeta(3, (int[]){expr, ADD_ASSIGN, expr}),
        [60].alpha = expr,          [60].beta = makeBeta(3, (int[]){expr, SUB_ASSIGN, expr}),
        [61].alpha = expr,          [61].beta = makeBeta(3, (int[]){expr, AND, expr}),
        [62].alpha = expr,          [62].beta = makeBeta(3, (int[]){expr, OR, expr}),
        [63].alpha = expr,          [63].beta = makeBeta(3, (int[]){expr, EQUALS, expr}),
        [64].alpha = expr,          [64].beta = makeBeta(3, (int[]){expr, N_EQUALS, expr}),
        [65].alpha = expr,          [65].beta = makeBeta(3, (int[]){expr, COMMA, expr}),
        [66].alpha = expr,          [66].beta = makeBeta(3, (int[]){expr, APPLY_GATES, expr_quantum}),
        [67].alpha = expr,          [67].beta = makeBeta(3, (int[]){expr, IDENTIFIER_DOT, expr}),
        [68].alpha = expr_quantum,  [68].beta = makeBeta(3, (int[]){EXPR_PARANTHESIS_OPEN, expr_quantum, EXPR_PARANTHESIS_CLOSE}),
        [69].alpha = expr_quantum,  [69].beta = makeBeta(3, (int[]){expr_quantum, GATE_SEPARATOR, expr_quantum}),

        [70].alpha = print,         [70].beta = makeBeta(4, (int[]){TX_TO_FUNC, EXPR_PARANTHESIS_OPEN, expr, EXPR_PARANTHESIS_CLOSE}),
        [71].alpha = save,          [71].beta = makeBeta(4, (int[]){TX_TO_FUNC, EXPR_PARANTHESIS_OPEN, expr, EXPR_PARANTHESIS_CLOSE}),
        [72].alpha = expr,          [72].beta = makeBeta(4, (int[]){expr, IDX_BRACKET_OPEN, expr, IDX_BRACKET_CLOSE}),

        [73].alpha = paramdecl,     [73].beta = makeBeta(5, (int[]){paramdecl, COMMA, IDENTIFIER, COLON_COLON, dataType}),
        [74].alpha = stmt,          [74].beta = makeBeta(5, (int[]){IF, EXPR_PARANTHESIS_OPEN, expr, EXPR_PARANTHESIS_CLOSE, stmt}),
        [75].alpha = stmt,          [75].beta = makeBeta(5, (int[]){WHILE, EXPR_PARANTHESIS_OPEN, expr, EXPR_PARANTHESIS_CLOSE, stmt}),
        [76].alpha = stmt,          [76].beta = makeBeta(5, (int[]){ELIF, EXPR_PARANTHESIS_OPEN, expr, EXPR_PARANTHESIS_CLOSE, stmt}),
        [77].alpha = vardef_array,  [77].beta = makeBeta(5, (int[]){IDENTIFIER, IDX_BRACKET_OPEN, IDX_BRACKET_CLOSE, ASSIGN, expr}),
        [78].alpha = print,         [78].beta = makeBeta(5, (int[]){COLON_COLON, EXPR_PARANTHESIS_OPEN, expr, EXPR_PARANTHESIS_CLOSE, print}),
        [79].alpha = save,          [79].beta = makeBeta(5, (int[]){COLON_COLON, EXPR_PARANTHESIS_OPEN, expr, EXPR_PARANTHESIS_CLOSE, save}),
        [80].alpha = expr,          [80].beta = makeBeta(5, (int[]){NEW, dataType, EXPR_PARANTHESIS_OPEN, expr, EXPR_PARANTHESIS_CLOSE}),
        [81].alpha = expr,          [81].beta = makeBeta(5, (int[]){expr, TX_TO_FUNC, EXPR_PARANTHESIS_OPEN, expr, EXPR_PARANTHESIS_CLOSE}),
        [82].alpha = expr,          [82].beta = makeBeta(5, (int[]){expr, IF_THEN_ELSE, expr, IF_THEN_ELSE, expr}),
        [83].alpha = expr,          [83].beta = makeBeta(5, (int[]){expr, INPUT, EXPR_PARANTHESIS_OPEN, expr, EXPR_PARANTHESIS_CLOSE}),

        [84].alpha = functions,     [84].beta = makeBeta(8, (int[]){FUNC, COLON_COLON, dataType, IDENTIFIER, RX_FROM_FUNC, EXPR_PARANTHESIS_OPEN, EXPR_PARANTHESIS_CLOSE, stmt}),

        [85].alpha = functions,     [85].beta = makeBeta(9, (int[]){FUNC, COLON_COLON, dataType, IDENTIFIER, RX_FROM_FUNC, EXPR_PARANTHESIS_OPEN, paramdecls, EXPR_PARANTHESIS_CLOSE, stmt}),
        [86].alpha = stmt,          [86].beta = makeBeta(9, (int[]){FOR, EXPR_PARANTHESIS_OPEN, expr, IN, expr, RANGE, expr, EXPR_PARANTHESIS_CLOSE, stmt})
    };

    prod = p;
}

bool isEqual(int *beta, int *buf, int len) {
    int i;
    for(i = 0; i < len; i++) {
        if(beta[i] != buf[i]) {
            return false;
        }
    }
    return true;
}

#endif