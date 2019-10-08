#ifndef QUANTUM_PARSER_H
#define QUANTUM_PARSER_H

typedef struct hm {
	char *token;
	FILE f;
	struct hm *next;
}FuncHashMap;

FuncHashMap* addToken(FuncHashMap *hm, char *t, FILE *fptr) {
	FuncHashMap *h = (FuncHashMap*) malloc(sizeof(FuncHashMap));
	h->token = (char*) malloc(strlen(t) * sizeof(char));



	strcpy(h->token, t);
	h->f = *fptr;
	h->next = hm;

	return h;
}

void printHM(FuncHashMap *hm) {
	printf("FuncName\tLineNum\n");
	while(hm) {
		printf("%s\n", hm->token);
		hm = hm->next;
	}
}

void apply_Program(FILE *fp) {
	char ch, name[25], cur_token[20], prev_token[20];
	int line_count = 0, i = 0;
	FuncHashMap *funcs = NULL;
	FILE ret_line_ptr, cur_func_line_ptr;
	quReg *qr;
	bool qureg_init = false, got_name = false, got_prec = false, building_token = true, function_active = false;
	bool start_col = false;
	int gate_num = 0;
	int count = 0;

	while((ch = fgetc(fp)) != EOF) {
		if(ch == '#') {
			building_token = false;
			while(fgetc(fp) != '\n');
			line_count++;
		}
		else if(isalnum(ch) || ch == '_') {
			cur_token[i++] = ch;
			building_token = true;
		}
		else if(ch == '"') {
			while((ch = fgetc(fp)) != '"') {
				cur_token[i++] = ch;
			}
		}
		else if(ch == ' ' || ch == '\n' || ch == '{' || ch == '.' || ch == ',') {
			cur_token[i] = '\0';
			building_token = false;
			i = 0;

			if(!strcmp(prev_token, "func")) {
				int n = 0;
				while(fgetc(fp) != '\n') {
					n++;
				}
				n += 2;
				fseek(fp, 1, SEEK_CUR);
				funcs = addToken(funcs, cur_token, fp);
				fseek(fp, -n, SEEK_CUR);
			}

			strcpy(prev_token, cur_token);

			if(ch == '{') {
				while((ch = fgetc(fp)) != '}') {
					if(ch == '\n') {
						line_count++;
					}
				}
			}
		}

		// Init the quReg
		if(!strcmp(cur_token, "init") && !qureg_init) {
			fseek(fp, 1, SEEK_CUR);
			int size = fgetc(fp) - '0';
			if((ch = fgetc(fp)) != ']')
				size = (size * 10) + (ch - '0');
			qr = newQuReg(size);

			qureg_init = true;
		}
		// Getting name of quReg
		else if(!strcmp(cur_token, "name") && !got_name) {
			int j = 0;
			while(fgetc(fp) != '"');

			while((ch = fgetc(fp)) != '"') {
				name[j++] = ch;
			}
			name[j] = '\0';
			got_name = true;
		}
		// Getting precision
		else if(!strcmp(cur_token, "prec") && !got_prec) {
			while(!isdigit(ch = fgetc(fp)));

			int prec = ch - '0';
			if((ch = fgetc(fp)) != '\n')
				prec = (prec * 10) + (ch - '0');
			fseek(fp, -1, SEEK_CUR);

			setPrecision(prec);
			got_prec = true;
		}
		else if(!strcmp(cur_token, "Pnz")) {
			printf("%s", name);
			Qprint("%r\n", qr);
		}
		else if(!strcmp(cur_token, "Pa")) {
			printf("%s", name);
			Qprint("%a\n", qr);
		}

		else if(qureg_init && got_name && got_prec) {
			FuncHashMap *head = funcs;
			while(head != NULL) {
				// printf("test: %s\t%s\n", head->token, cur_token);
				if(!strcmp(head->token, cur_token)) {
					// printf("test2\n");
					ret_line_ptr = *fp;
					*fp = head->f;
					function_active = true;
					break;
				}
				head = head->next;
			}

			// THE MAIN PART !!!!!!
			if(function_active) {
				while((ch = fgetc(fp)) != '}') {
					char next_ch;

					if(start_col == false && ch == '[')
						start_col = true;
					else if(ch == ']') {
						start_col = false;
						gate_num = 0;
					}

					if(ch == '#') {
						while((ch = fgetc(fp)) != '\n');
					}

					if(ch == 'P') {
						if((ch = fgetc(fp)) == 'a') {
							printf("%s", name);
							Qprint("%a\n", qr);
						}
						else if(ch == 'n' && (next_ch = fgetc(fp)) == 'z') {
							printf("%s", name);
							Qprint("%r\n", qr);
						}
					}

					if(start_col) {
						if(ch == ',' || ch == ' ') {
						}
						else if(ch == 'X') {
							qr = X_reg(qr, gate_num);
							gate_num = (gate_num+1) % qr->size;
						}
						else if(ch == 'Y') {
							qr = Y_reg(qr, gate_num);
							gate_num = (gate_num+1) % qr->size;
						}
						else if(ch == 'Z') {
							qr = Z_reg(qr, gate_num);
							gate_num = (gate_num+1) % qr->size;
						}
						else if(ch == 'H') {
							qr = H_reg(qr, gate_num);
							gate_num = (gate_num+1) % qr->size;
						}
						else if(ch == 'S') {
							if((ch = fgetc(fp)) == 'x') {
								int idx1, idx2 = -1;
								idx1 = gate_num;

								while(ch != 'S' && (next_ch = fgetc(fp)) != 'x') {
									if(ch == ']') {
										printf("[!] Invalid expression... There should be 2 swap gates together.\n");
										printf("Exiting...\n");
										exit(0);
									}
									else if (ch == ',')
										gate_num = (gate_num+1) % qr->size;
								}

								idx2 = gate_num;
								QSwap_reg(qr, idx1, idx2);
							}
							else {
								qr = S_reg(qr, gate_num);
								fseek(fp, -1, SEEK_CUR);
							}
							gate_num = (gate_num+1) % qr->size;
						}
						else if(ch == 'R') {
							fseek(fp, 2, SEEK_CUR);
							int count = 0;
							double angle;
							int decimal = 0;
							bool negative = false;
							for(int j = 0; ; j++, i++) {
								if((ch = fgetc(fp)) == '-')
									negative = true;

								if(isalnum(ch)) {
									if(!decimal) {
										angle = angle * 10 + (ch - '0');
									}
									else if(decimal) {
										count++;
										double summand = (double) (ch - '0') / pow(10, count);
										angle = angle + summand;
									}
								}
								else if(ch == '.') {
									decimal = 1;
								}

								if(ch == '(' || ch == ',')
									break;
							}
							fseek(fp, -1, SEEK_CUR);
							angle = angle * PI / 180;
							angle = negative ? -1 * angle : angle;
							qr = R_reg(angle, qr, gate_num);
							gate_num = (gate_num+1) % qr->size;
							angle = 0;
						}
						else if(ch == 'C') {
							int *idxs = (int*) malloc(qr->size * sizeof(int));
							bool cnot = false;

							for(int j = 0; j < qr->size; j++)
								idxs[j] = 0;

							if((ch = fgetc(fp)) == 'o') {
								idxs[gate_num] = -1;
								cnot = true;
							}
							else if(ch == 'x') {
								idxs[gate_num] = 1;
								cnot = true;
							}

							if(cnot) {
								while((ch = fgetc(fp)) != ']') {
									if(ch == 'C' && (next_ch = fgetc(fp)) == 'o')
										idxs[gate_num] = -1;
									else if(ch == 'C' && next_ch == 'x')
										idxs[gate_num] = 1;

									if(ch == ',')
										gate_num = (gate_num+1) % qr->size;
								}
							}

							CNOT_reg(qr, idxs);
							gate_num = (gate_num+1) % qr->size;
						}
						else if(ch == '-') {
							gate_num = (gate_num+1) % qr->size;
						}
					}
				}
				cur_token[0] = '\0';
				*fp = ret_line_ptr;
				function_active = false;
			}
		}

		if(ch == '\n') {
			line_count++;
		}
	}
}

#endif