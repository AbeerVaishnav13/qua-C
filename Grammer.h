#ifndef GRAMMER_H
#define GRAMMER_H

#define HASH_FUNC(val, beta, first, len) ((((val + beta) << 1) ^ first) ^ len)

#define NUM_PRODUCTIONS 90

#define one_production 29
#define two_production 12
#define three_production 29
#define four_production 1
#define five_production 13
#define eight_production 3
#define nine_production 2

#define ONE_PRODUCTION one_production
#define TWO_PRODUCTION (ONE_PRODUCTION + two_production)
#define THREE_PRODUCTION (TWO_PRODUCTION + three_production)
#define FOUR_PRODUCTION (THREE_PRODUCTION + four_production)
#define FIVE_PRODUCTION (FOUR_PRODUCTION + five_production)
#define EIGHT_PRODUCTION (FIVE_PRODUCTION + eight_production)
#define NINE_PRODUCTION (EIGHT_PRODUCTION + nine_production)

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

unsigned int alpha1[one_production] =   {   paramdecls, stmt, com_stmt, dataType, dataType,
                                            dataType, dataType, dataType, dataType, dataType, 
                                            expr, expr, expr, expr_quantum, expr_quantum, expr_quantum,
                                            expr_quantum, expr_quantum, expr_quantum, expr_quantum, expr_quantum, 
                                            expr_quantum, expr_quantum, expr_quantum, expr_quantum, vardef_single, expr,
                                            stmt, stmt
                                        };

unsigned int beta1[one_production] =  { 214, 31, 13, 35, 32, 97, 103, 98, 42, 47, 2, 7, 4, 193, 203, 217, 196, 205,
                                        206, 200, 194, 67, 64, 218, 199, 1, 1, 244, 253 };

unsigned int alpha2[two_production] =   {   functions, stmt, stmt, stmt, stmt, com_stmt, vardefs, vardefs, expr,
                                            expr, expr, expr
                                        };

unsigned int beta2[two_production] =  {  541, 509, 197, 426, 592, 527, 715, 713, 417, 344, 622, 616  };

unsigned int alpha3[three_production] = {   paramdecl, stmt, vardefs, vardef_single, vardef_array,
                                            expr, expr, expr, expr, expr, expr, expr, expr, expr,
                                            expr, expr, expr, expr, expr, expr, expr, expr, expr, expr, expr,
                                            expr, expr, expr_quantum, expr_quantum
                                        };

unsigned int beta3[three_production] =  {   219, 449, 951, 373, 121, 464, 626, 1159, 1263, 1279, 1215, 1163,
                                            1207, 1251, 1171, 1183, 1259, 1175, 1371, 1351, 1347, 1359, 1275,
                                            1255, 1111, 1497, 1391, 468, 1390   };

unsigned int alpha4[four_production] =   { expr };

unsigned int beta4[four_production] = { 2562 };

unsigned int alpha5[five_production] =  {   paramdecl, stmt, stmt, stmt, vardef_array, print, print, save, save, expr,
                                            expr, expr, expr
                                        };

unsigned int beta5[five_production] = {   3934, 1734, 2838, 1647, 823, 1527, 1999, 1292, 1812, 3097, 4809, 5041, 5849 };

unsigned int alpha8[eight_production] = { functions, print, save };

unsigned int beta8[eight_production] =    {   11166, 13012, 13743 };

unsigned int alpha9[nine_production] = { functions, stmt };

unsigned int beta9[nine_production] = {   22641, 27680    };


// typedef struct p {
//     int alpha;
//     int *beta;
// }Production;

// int* makeBeta(int len, int arr[]) {
// 	int *Arr = (int*) malloc(len * sizeof(int));
// 	for(int i = 0; i < len; i++) {
// 		Arr[i] = arr[i];
// 	}
// 	return Arr;
// }

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

// void initProductions(Production *prod) {
//     Production p[87] = {
//         [0].alpha = paramdecls,     [0].beta = makeBeta(1, (int[]){paramdecl}),
//         [1].alpha = stmt,           [1].beta = makeBeta(1, (int[]){END_OF_LINE}),
//         [2].alpha = com_stmt,       [2].beta = makeBeta(1, (int[]){CMPND_STMT_OPEN}),
//         [3].alpha = dataType,       [3].beta = makeBeta(1, (int[]){INT}),
//         [4].alpha = dataType,       [4].beta = makeBeta(1, (int[]){CHAR}),
//         [5].alpha = dataType,       [5].beta = makeBeta(1, (int[]){BOOL}),
//         [6].alpha = dataType,       [6].beta = makeBeta(1, (int[]){FLOAT}),
//         [7].alpha = dataType,       [7].beta = makeBeta(1, (int[]){VOID}),
//         [8].alpha = dataType,       [8].beta = makeBeta(1, (int[]){QUREG}),
//         [9].alpha = dataType,       [9].beta = makeBeta(1, (int[]){QUBIT}),
//         [10].alpha = expr,          [10].beta = makeBeta(1, (int[]){INT_LITERAL}),
//         [11].alpha = expr,          [11].beta = makeBeta(1, (int[]){FLOAT_LITERAL}),
//         [12].alpha = expr,          [12].beta = makeBeta(1, (int[]){STRING_LITERAL}),
//         [13].alpha = expr_quantum,  [13].beta = makeBeta(1, (int[]){HADAMARD}),
//         [14].alpha = expr_quantum,  [14].beta = makeBeta(1, (int[]){PHASE}),
//         [15].alpha = expr_quantum,  [15].beta = makeBeta(1, (int[]){ROTATION}),
//         [16].alpha = expr_quantum,  [16].beta = makeBeta(1, (int[]){PAULI_X}),
//         [17].alpha = expr_quantum,  [17].beta = makeBeta(1, (int[]){PAULI_Y}),
//         [18].alpha = expr_quantum,  [18].beta = makeBeta(1, (int[]){PAULI_Z}),
//         [19].alpha = expr_quantum,  [19].beta = makeBeta(1, (int[]){QFT}),
//         [20].alpha = expr_quantum,  [20].beta = makeBeta(1, (int[]){INV_QFT}),
//         [21].alpha = expr_quantum,  [21].beta = makeBeta(1, (int[]){CNOT_o}),
//         [22].alpha = expr_quantum,  [22].beta = makeBeta(1, (int[]){CNOT_x}),
//         [23].alpha = expr_quantum,  [23].beta = makeBeta(1, (int[]){SWAP}),
//         [24].alpha = expr_quantum,  [24].beta = makeBeta(1, (int[]){NOOP}),

//         [25].alpha = functions,     [25].beta = makeBeta(2, (int[]){functions, functions}),
//         [26].alpha = stmt,          [26].beta = makeBeta(2, (int[]){com_stmt, CMPND_STMT_CLOSE}),
//         [27].alpha = stmt,          [27].beta = makeBeta(2, (int[]){ELSE, stmt}),
//         [28].alpha = stmt,          [28].beta = makeBeta(2, (int[]){vardefs, END_OF_LINE}),
//         [29].alpha = stmt,          [29].beta = makeBeta(2, (int[]){expr, END_OF_LINE}),
//         [30].alpha = com_stmt,      [30].beta = makeBeta(2, (int[]){com_stmt, stmt}),
//         [31].alpha = vardefs,       [31].beta = makeBeta(2, (int[]){dataType, vardef_single}),
//         [32].alpha = vardefs,       [32].beta = makeBeta(2, (int[]){dataType, vardef_array}),
//         [33].alpha = expr,          [33].beta = makeBeta(2, (int[]){INC, expr}),
//         [34].alpha = expr,          [34].beta = makeBeta(2, (int[]){DEC, expr}),
//         [35].alpha = expr,          [35].beta = makeBeta(2, (int[]){expr, INC}),
//         [36].alpha = expr,          [36].beta = makeBeta(2, (int[]){expr, DEC}),
        
//         [37].alpha = paramdecl,     [37].beta = makeBeta(3, (int[]){IDENTIFIER, COLON_COLON, dataType}),
//         [38].alpha = stmt,          [38].beta = makeBeta(3, (int[]){RETURN, expr, END_OF_LINE}),
//         [39].alpha = stmt,          [39].beta = makeBeta(3, (int[]){PRINT, print, END_OF_LINE}),
//         [40].alpha = stmt,          [40].beta = makeBeta(3, (int[]){SAVE, save, END_OF_LINE}),
//         [41].alpha = vardefs,       [41].beta = makeBeta(3, (int[]){vardefs, COMMA, vardef_single}),
//         [42].alpha = vardef_single, [42].beta = makeBeta(3, (int[]){IDENTIFIER, ASSIGN, expr}),
//         [43].alpha = vardef_array,  [43].beta = makeBeta(3, (int[]){IDENTIFIER, IDX_BRACKET_OPEN, IDX_BRACKET_CLOSE}),
//         [44].alpha = print,         [44].beta = makeBeta(3, (int[]){COLON_COLON, PRINT_FORMAT, print}),
//         [45].alpha = save,          [45].beta = makeBeta(3, (int[]){COLON_COLON, PRINT_FORMAT, save}),
//         [46].alpha = expr,          [46].beta = makeBeta(3, (int[]){EXPR_PARANTHESIS_OPEN, expr, EXPR_PARANTHESIS_CLOSE}),
//         [47].alpha = expr,          [47].beta = makeBeta(3, (int[]){IDX_BRACKET_OPEN, expr, IDX_BRACKET_CLOSE}),
//         [48].alpha = expr,          [48].beta = makeBeta(3, (int[]){expr, EXPR_PARANTHESIS_OPEN,  EXPR_PARANTHESIS_CLOSE}),
//         [49].alpha = expr,          [49].beta = makeBeta(3, (int[]){expr, ASSIGN, expr}),
//         [50].alpha = expr,          [50].beta = makeBeta(3, (int[]){expr, ASSIGN, stmt}),
//         [51].alpha = expr,          [51].beta = makeBeta(3, (int[]){expr, ADD, expr}),
//         [52].alpha = expr,          [52].beta = makeBeta(3, (int[]){expr, SUB, expr}),
//         [53].alpha = expr,          [53].beta = makeBeta(3, (int[]){expr, MULT, expr}),
//         [54].alpha = expr,          [54].beta = makeBeta(3, (int[]){expr, DIV, expr}),
//         [55].alpha = expr,          [55].beta = makeBeta(3, (int[]){expr, GT, expr}),
//         [56].alpha = expr,          [56].beta = makeBeta(3, (int[]){expr, LT, expr}),
//         [57].alpha = expr,          [57].beta = makeBeta(3, (int[]){expr, GTET, expr}),
//         [58].alpha = expr,          [58].beta = makeBeta(3, (int[]){expr, LTET, expr}),
//         [59].alpha = expr,          [59].beta = makeBeta(3, (int[]){expr, ADD_ASSIGN, expr}),
//         [60].alpha = expr,          [60].beta = makeBeta(3, (int[]){expr, SUB_ASSIGN, expr}),
//         [61].alpha = expr,          [61].beta = makeBeta(3, (int[]){expr, AND, expr}),
//         [62].alpha = expr,          [62].beta = makeBeta(3, (int[]){expr, OR, expr}),
//         [63].alpha = expr,          [63].beta = makeBeta(3, (int[]){expr, EQUALS, expr}),
//         [64].alpha = expr,          [64].beta = makeBeta(3, (int[]){expr, N_EQUALS, expr}),
//         [65].alpha = expr,          [65].beta = makeBeta(3, (int[]){expr, COMMA, expr}),
//         [66].alpha = expr,          [66].beta = makeBeta(3, (int[]){expr, APPLY_GATES, expr_quantum}),
//         [67].alpha = expr,          [67].beta = makeBeta(3, (int[]){expr, IDENTIFIER_DOT, expr}),
//         [68].alpha = expr_quantum,  [68].beta = makeBeta(3, (int[]){EXPR_PARANTHESIS_OPEN, expr_quantum, EXPR_PARANTHESIS_CLOSE}),
//         [69].alpha = expr_quantum,  [69].beta = makeBeta(3, (int[]){expr_quantum, GATE_SEPARATOR, expr_quantum}),

//         [70].alpha = print,         [70].beta = makeBeta(4, (int[]){TX_TO_FUNC, EXPR_PARANTHESIS_OPEN, expr, EXPR_PARANTHESIS_CLOSE}),
//         [71].alpha = save,          [71].beta = makeBeta(4, (int[]){TX_TO_FUNC, EXPR_PARANTHESIS_OPEN, expr, EXPR_PARANTHESIS_CLOSE}),
//         [72].alpha = expr,          [72].beta = makeBeta(4, (int[]){expr, IDX_BRACKET_OPEN, expr, IDX_BRACKET_CLOSE}),

//         [73].alpha = paramdecl,     [73].beta = makeBeta(5, (int[]){paramdecl, COMMA, IDENTIFIER, COLON_COLON, dataType}),
//         [74].alpha = stmt,          [74].beta = makeBeta(5, (int[]){IF, EXPR_PARANTHESIS_OPEN, expr, EXPR_PARANTHESIS_CLOSE, stmt}),
//         [75].alpha = stmt,          [75].beta = makeBeta(5, (int[]){WHILE, EXPR_PARANTHESIS_OPEN, expr, EXPR_PARANTHESIS_CLOSE, stmt}),
//         [76].alpha = stmt,          [76].beta = makeBeta(5, (int[]){ELIF, EXPR_PARANTHESIS_OPEN, expr, EXPR_PARANTHESIS_CLOSE, stmt}),
//         [77].alpha = vardef_array,  [77].beta = makeBeta(5, (int[]){IDENTIFIER, IDX_BRACKET_OPEN, IDX_BRACKET_CLOSE, ASSIGN, expr}),
//         [78].alpha = print,         [78].beta = makeBeta(5, (int[]){COLON_COLON, EXPR_PARANTHESIS_OPEN, expr, EXPR_PARANTHESIS_CLOSE, print}),
//         [79].alpha = save,          [79].beta = makeBeta(5, (int[]){COLON_COLON, EXPR_PARANTHESIS_OPEN, expr, EXPR_PARANTHESIS_CLOSE, save}),
//         [80].alpha = expr,          [80].beta = makeBeta(5, (int[]){NEW, dataType, EXPR_PARANTHESIS_OPEN, expr, EXPR_PARANTHESIS_CLOSE}),
//         [81].alpha = expr,          [81].beta = makeBeta(5, (int[]){expr, TX_TO_FUNC, EXPR_PARANTHESIS_OPEN, expr, EXPR_PARANTHESIS_CLOSE}),
//         [82].alpha = expr,          [82].beta = makeBeta(5, (int[]){expr, IF_THEN_ELSE, expr, IF_THEN_ELSE, expr}),
//         [83].alpha = expr,          [83].beta = makeBeta(5, (int[]){expr, INPUT, EXPR_PARANTHESIS_OPEN, expr, EXPR_PARANTHESIS_CLOSE}),

//         [84].alpha = functions,     [84].beta = makeBeta(8, (int[]){FUNC, COLON_COLON, dataType, IDENTIFIER, RX_FROM_FUNC, EXPR_PARANTHESIS_OPEN, EXPR_PARANTHESIS_CLOSE, stmt}),

//         [85].alpha = functions,     [85].beta = makeBeta(9, (int[]){FUNC, COLON_COLON, dataType, IDENTIFIER, RX_FROM_FUNC, EXPR_PARANTHESIS_OPEN, paramdecls, EXPR_PARANTHESIS_CLOSE, stmt}),
//         [86].alpha = stmt,          [86].beta = makeBeta(9, (int[]){FOR, EXPR_PARANTHESIS_OPEN, expr, IN, expr, RANGE, expr, EXPR_PARANTHESIS_CLOSE, stmt})
//     };

//     prod = p;
//     printf("Productions  made\n");
// }

// bool isEqual(int *beta, int *buf, int len) {
//     int i;
//     printf("\n\n\n");
//     for(i = 0; i < len; i++) {
//         printf("\tbeta[%d]: %d, buf[%d]: %d\n", i, beta[i], i, buf[i]);
//         if(beta[i] != buf[i]) {
//             printf("\tNot Equal => beta[%d]: %d, buf[%d]: %d\n", i, beta[i], i, buf[i]);
//             return false;
//         }
//     }
//     return true;
// }

unsigned int hashIt(int *buf, int len) {
    unsigned int exored_val = 0;
    for(int i = 0; i < len; i++) {
        exored_val = HASH_FUNC(exored_val, buf[i], buf[0], len);
    }

    return exored_val;
}

unsigned int hashItSingle(int beta) {
    return HASH_FUNC(0, beta, beta, 1);
}

#endif