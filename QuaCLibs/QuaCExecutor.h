#ifndef QUANTUM_EXECUTOR_H
#define QUANTUM_EXECUTOR_H

typedef struct im {
	char *token;
	int idx;
	struct im *next;
}IdentifierMap;

IdentifierMap* addToken(IdentifierMap *im, char *t, int index) {
	IdentifierMap *i = (IdentifierMap*) malloc(sizeof(IdentifierMap));
	i->token = (char*) malloc(strlen(t) * sizeof(char));

	strcpy(i->token, t);
	i->idx = index;
	i->next = im;

	return i;
}

void printIM(IdentifierMap *im) {
	printf("IdentifierName\tIndex\n");
	while(im) {
		printf("%s\t\t%d\n", im->token, im->idx);
		im = im->next;
	}
	printf("\n");
}

IdentifierMap* getIdentifier(char *identifier, IdentifierMap *imap) {
	IdentifierMap *im = imap;
	while(im) {
		if(!strcmp(identifier, im->token)) break;
		im = im->next;
	}
	return im;
}

typedef struct qm {
	char *token;
	char *userName;
	int size;
	int count;
	bool uname_set;
	struct qm *next;
}QuregMap;

QuregMap* addQureg(QuregMap *qm, char *t, int size, int index, char *name, char count) {
	QuregMap *q = (QuregMap*) malloc(sizeof(QuregMap));
	q->token = (char*) malloc(strlen(t) * sizeof(char));

	strcpy(q->token, t);
	q->size = size;
	q->userName = (char*) malloc(strlen(name) * sizeof(char));
	strcpy(q->userName, name);
	q->count = count;
	q->next = qm;
	q->uname_set = false;

	return q;
}

void alterUserName(QuregMap *qm, char *name) {
	int i;

	if(!qm->uname_set) {
		qm->userName = (char*) realloc(qm->userName, strlen(name) * sizeof(char));
		strcpy(qm->userName, name);
		qm->uname_set = true;
	}
}

void printQM(QuregMap *qm) {
	printf("Qureg Name\tSize\tUserName\n");
	while(qm) {
		printf("%s\t\t%d\t%s\n", qm->token, qm->size, qm->userName);
		qm = qm->next;
	}
	printf("\n");
}

QuregMap* getQureg(char *identifier, QuregMap *qmap) {
	QuregMap *qm = qmap;
	while(qm) {
		if(!strcmp(identifier, qm->token)) break;
		qm = qm->next;
	}
	return qm;
}


// Prototypes
void executeFunc(KeyTypes *keytypes, IdentifierMap *gates, int i, int qureg_size, quReg *qr, QuregMap *qm);
void executeGate(KeyTypes *keytypes, int i, quReg *qr, int gates_done);
void executePrint(char *cmd, quReg *qr, QuregMap *qm);

void RunProgram(KeyTypes *kt) {
	printf("Executing program...\n");
	int i = 0;
	IdentifierMap *funcs = NULL;
	IdentifierMap *gates = NULL;
	QuregMap *quregs = NULL;
	short qureg_count = 0;
	quReg *qr1 = NULL, *qr2 = NULL, *qr3 = NULL;

	int ret_i_val = -1;

	short qr1_size = 0, qr2_size = 0, qr3_size = 0;
	short func_qubit_count = 0;
	short gate_qubit_count = 0;
	short cur_gate_qubit_count = 0;

	while(kt[i].type != LIST_END) {
		if(kt[i].type == GATE) {
			gates = addToken(gates, kt[i+1].key, i+1);
			while(kt[i].type != CMPND_STMT_CLOSE) i++;
		}
		else if(kt[i].type == FUNC) {
			funcs = addToken(funcs, kt[i+1].key, i+1);
			while(kt[i].type != CMPND_STMT_CLOSE) i++;
		}
		else if(kt[i].type == QUREG && kt[i+1].type == IDENTIFIER) {
			int size = atoi(kt[i+6].key);
			qureg_count += 1;
			if(qureg_count <= 3)
				quregs = addQureg(quregs, kt[i+1].key, size, -1, kt[i+1].key, qureg_count);
			else if(qureg_count == 4)
				printf("[!] Currently the language only supports upto 3 quregs with upto 30 qubits each. Ignoring all other qureg declarations.\n");

			if(qureg_count == 1) {
				qr1_size = size;
				qr1 = newQuReg(qr1_size);
			}
			else if(qureg_count == 2) {
				qr2_size = size;
				qr2 = newQuReg(qr2_size);
			}
			else if(qureg_count == 3) {
				qr3_size = size;
				qr3 = newQuReg(qr3_size);
			}

			while(kt[i].type != IDX_BRACKET_CLOSE) i++;
			i++;


			if(kt[i].type == REG_NAME) {
				alterUserName(quregs, kt[i+1].key);
				i++;
			}
		}
		else if(kt[i].type == PRINT) {
			if(!strcmp(kt[i].key, "Pa")) {
				QuregMap *qm = getQureg(kt[i-2].key, quregs);
				quReg *qr = (qm->count == 1) ? qr1 : ((qm->count == 2) ? qr2 : ((qm->count == 3) ? qr3 : NULL));
				if(qr != NULL) {
					printf("%s = ", qm->userName);
					Qprint("\t%a\n", qr);
				}
				else {
					printf("[!] Identifier %s not defined.\n", qm->token);
					exit(0);
				}
			}
			else if(!strcmp(kt[i].key, "Pnz")){
				QuregMap *qm = getQureg(kt[i-2].key, quregs);
				quReg *qr = (qm->count == 1) ? qr1 : ((qm->count == 2) ? qr2 : ((qm->count == 3) ? qr3 : NULL));
				if(qr != NULL) {
					printf("%s = ", qm->userName);
					Qprint("\t%r\n", qr);
				}
				else {
					printf("[!] Identifier %s not defined.\n", qm->token);
					exit(-1);
				}
			}
		}
		else if(!strcmp(kt[i].key, "setPrecision")) {
			i += 2;
			setPrecision(atoi(kt[i].key));
			i++;
		}
		else if(kt[i].type == IDENTIFIER) {
			IdentifierMap *im;
			QuregMap *qm;
			quReg *qr;

			if((im = getIdentifier(kt[i].key, funcs))) {
				if(kt[i+1].type == EXPR_PARANTHESIS_OPEN && kt[i+2].type == EXPR_PARANTHESIS_CLOSE) {
					qm = getQureg(kt[i-2].key, quregs);
					ret_i_val = i + 1;
					i = im->idx;
					quReg *qr = (qm->count == 1) ? qr1 : ((qm->count == 2) ? qr2 : ((qm->count == 3) ? qr3 : NULL));
					executeFunc(kt, gates, i, qr->size, qr, qm);
					i = ret_i_val;
				}
				else {
					printf("[!] Expected '()' after a function identifier.\n");
					exit(-1);
				}
			}
			else if((im = getIdentifier(kt[i].key, gates))) {
				printf("[!] Gates can only be used inside functions. Move the usage of %s gate to a 'func' block.\n", kt[i].key);
				exit(-1);
			}
			else if((qm = getQureg(kt[i].key, quregs))) {

			}
			else {
				printf("[!] Use of undeclared identifier '%s'.\n", kt[i].key);
				exit(-1);
			}
		}

		i++;
	}
	// printIM(funcs);
	// printIM(gates);
	// printQM(quregs);
}

void executePrint(char *cmd, quReg *qr, QuregMap *qm) {
	if(!strcmp(cmd, "Pa")) {
		printf("%s = ", qm->userName);
		Qprint("\t%a\n", qr);
	}
	else if(!strcmp(cmd, "Pnz")){
		printf("%s = ", qm->userName);
		Qprint("\t%r\n", qr);
	}
}

void executeFunc(KeyTypes *keytypes, IdentifierMap *gates, int i, int qureg_size, quReg *qr, QuregMap *qm) {
	int cur_gate_num = 0;
	int ret_i_val_func = 0;
	char *func_name = (char*) malloc(strlen(keytypes[i].key) * sizeof(char));
	strcpy(func_name, keytypes[i].key);

	IdentifierMap *imap;

	while(keytypes[i].type != IDX_BRACKET_OPEN) i++;

	while(keytypes[i].type != CMPND_STMT_CLOSE) {

		if(cur_gate_num > qureg_size) {
			printf("[!] Too many gates in the function '%s'. [number of gates: %d]\n", func_name, cur_gate_num);
			exit(-1);
		}

		if(keytypes[i].type == COMMA) {
		}
		else if(keytypes[i].type == IDX_BRACKET_CLOSE || keytypes[i].type == IDX_BRACKET_OPEN || keytypes[i].type == CMPND_STMT_CLOSE) {
			cur_gate_num = 0;
		}
		else if(keytypes[i].type == PAULI_X) {
			qr = X_reg(qr, cur_gate_num);
		}
		else if(keytypes[i].type == PAULI_Y) {
			qr = Y_reg(qr, cur_gate_num);
		}
		else if(keytypes[i].type == PAULI_Z) {
			qr = Z_reg(qr, cur_gate_num);
		}
		else if(keytypes[i].type == PHASE) {
			qr = S_reg(qr, cur_gate_num);
		}
		else if(keytypes[i].type == ROTATION) {
			int angle = atoi((keytypes[i].key + 2));
			qr = R_reg(angle, qr, cur_gate_num);
		}
		else if(keytypes[i].type == HADAMARD) {
			qr = H_reg(qr, cur_gate_num);
		}
		else if(keytypes[i].type == SWAP) {
			int idx2 = cur_gate_num;
			while(keytypes[i].type != SWAP) idx2++;
			
			qr = QSwap_reg(qr, cur_gate_num, idx2);
		}
		else if(keytypes[i].type == QFT) {
			printf("QFT Gate: This functionality is not added right now. Please wait for the next version to use this.\n");
			exit(0);
		}
		else if(keytypes[i].type == CONTROL) {
			printf("CONTROL Gate: This functionality is not added right now. Please wait for the next version to use this.\n");
			exit(0);
		}
		else if(keytypes[i].type == INV_CONTROL) {
			printf("INVERSE-CONTROL Gate: This functionality is not added right now. Please wait for the next version to use this.\n");
			exit(0);
		}
		else if(keytypes[i].type == X_AXIS_CONTROL) {
			printf("X-AXIS-CONTROL Gate: This functionality is not added right now. Please wait for the next version to use this.\n");
			exit(0);
		}
		else if(keytypes[i].type == Y_AXIS_CONTROL) {
			printf("Y-AXIS-CONTROL Gate: This functionality is not added right now. Please wait for the next version to use this.\n");
			exit(0);
		}
		else if(keytypes[i].type == IDENTITY) {

		}
		else if((imap = getIdentifier(keytypes[i].key, gates))) {
			ret_i_val_func = i + 1;
			i = imap->idx;
			executeGate(keytypes, i, qr, cur_gate_num);
			i = ret_i_val_func;
		}
		else if(keytypes[i].type == PRINT) {
			executePrint(keytypes[i].key, qr, qm);
			i += 2;
		}
		else {
			printf("[!] Invalid gate. Use one of the predefined or user defined gates.\n");
			exit(-1);
		}

		if(keytypes[i].type != COMMA && keytypes[i].type != IDX_BRACKET_OPEN && keytypes[i].type != IDX_BRACKET_CLOSE) {
			cur_gate_num += 1;
		}
		i++;
	}
}

void executeGate(KeyTypes *keytypes, int i, quReg *qr, int gates_done) {
	int gate_size = atoi(keytypes[i+2].key);
	int cur_qubit_idx = 0;
	int cur_gate_num = 0;
	char *gate_name = (char*) malloc(strlen(keytypes[i].key) * sizeof(char));
	strcpy(gate_name, keytypes[i].key);

	if((gate_size + gates_done) > qr->size) {
		printf("[!] Too many gates in the row. Resize the custom gate '%s' or decrease the number of pre-defined gates in the row. [%d]\n", keytypes[i].key, (gates_done + gate_size));
		exit(-1);
	}

	i += 2;

	while(keytypes[i].type != IDX_BRACKET_OPEN) i++;

	while(keytypes[i].type != CMPND_STMT_CLOSE) {
		if(cur_qubit_idx > gate_size) {
			printf("[!] Too many gates in the custom gate '%s'. [number of gates: %d]\n", gate_name, cur_qubit_idx);
			exit(-1);
		}

		cur_gate_num = gates_done + cur_qubit_idx;

		if(keytypes[i].type == COMMA) {
		}
		else if(keytypes[i].type == IDX_BRACKET_CLOSE || keytypes[i].type == IDX_BRACKET_OPEN || keytypes[i].type == CMPND_STMT_CLOSE) {
			cur_qubit_idx = 0;
		}
		else if(keytypes[i].type == PAULI_X) {
			qr = X_reg(qr, cur_gate_num);
		}
		else if(keytypes[i].type == PAULI_Y) {
			qr = Y_reg(qr, cur_gate_num);
		}
		else if(keytypes[i].type == PAULI_Z) {
			qr = Z_reg(qr, cur_gate_num);
		}
		else if(keytypes[i].type == PHASE) {
			qr = S_reg(qr, cur_gate_num);
		}
		else if(keytypes[i].type == ROTATION) {
			int angle = atoi((keytypes[i].key + 2));
			qr = R_reg(angle, qr, cur_gate_num);
		}
		else if(keytypes[i].type == HADAMARD) {
			qr = H_reg(qr, cur_gate_num);
		}
		else if(keytypes[i].type == SWAP) {
			int idx2 = cur_qubit_idx;
			while(keytypes[i].type != SWAP) idx2++;
			
			qr = QSwap_reg(qr, cur_gate_num, idx2);
		}
		else if(keytypes[i].type == QFT) {
			printf("QFT Gate: This functionality is not added right now. Please wait for the next version to use this.\n");
			exit(0);
		}
		else if(keytypes[i].type == CONTROL) {
			printf("CONTROL Gate: This functionality is not added right now. Please wait for the next version to use this.\n");
			exit(0);
		}
		else if(keytypes[i].type == INV_CONTROL) {
			printf("INVERSE-CONTROL Gate: This functionality is not added right now. Please wait for the next version to use this.\n");
			exit(0);
		}
		else if(keytypes[i].type == X_AXIS_CONTROL) {
			printf("X-AXIS-CONTROL Gate: This functionality is not added right now. Please wait for the next version to use this.\n");
			exit(0);
		}
		else if(keytypes[i].type == Y_AXIS_CONTROL) {
			printf("Y-AXIS-CONTROL Gate: This functionality is not added right now. Please wait for the next version to use this.\n");
			exit(0);
		}
		else if(keytypes[i].type == IDENTITY) {

		}
		else if(keytypes[i].type == PRINT) {
			printf("[!] Cannot use print statement inside a gate.\n");
			exit(-1);
		}
		else {
			printf("[!] Invalid gate. Use one of the predefined or user defined gates.\n");
			exit(-1);
		}

		if(keytypes[i].type != COMMA && keytypes[i].type != IDX_BRACKET_OPEN && keytypes[i].type != IDX_BRACKET_CLOSE) {
			cur_qubit_idx += 1;
		}
		i++;
	}
}

#endif