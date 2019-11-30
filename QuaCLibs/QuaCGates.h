#ifndef QUANTUMGATES_H

#define QUANTUMGATES_H

// Quantum NOT Gate:-
// Applies a NOT function to the probabilistic coefficients of the Qubit.
// This can also be assumed as rotation about X-axiz of the Bloch sphere
// For single qubit
quBit X(quBit x);
// For register of qubits
quReg* X_reg(quReg *qr, int idx);

// Rotation about Y-axis of the Bloch sphere
// For single qubit
quBit Y(quBit x);

// For register of qubits
quReg* Y_reg(quReg *qr, int idx);

// Rotation about Z-axis of the Bloch sphere
// For single qubit
quBit Z(quBit x);

// For register of qubits
quReg* Z_reg(quReg *qr, int idx);

// Quantum Hadamard Gate:-
// Applies hadamard Function to the Qubit passed into it.
// Puts the Qubit into superposition of |0> state and |1> state.
//Probability of getting both states after measuring is 50-50.
// For single qubit
quBit H(quBit x);

// For register of qubits
quReg* H_reg(quReg *qr, int idx);

//Quantum Phase Gate:-
// Changes the phase of the qubit
// For single qubit
quBit S(quBit x);

// For register of qubits
quReg* S_reg(quReg *qr, int idx);

// Quantum Rotation Gate:-
// Rotates the Coefficient of Quantum state about Complex Axis.
// angle should be in PI/k format, where k = 1, 2, 3, ...
// For single qubit
quBit R(double angle, quBit x);

// For register of qubits
quReg* R_reg(double angle, quReg *qr, int idx);

// Quantum CNOT Gate (Controlled NOT):-
// if (x1 == |1>) {x2 = X(x2)}
// else {x2 = x2}
// "Generally used for entanglement of the Qubits x1 and x2".
// For two different qubits
void CNOT(quBit *x1, quBit *x2);

// For register of qubits
quReg* CNOT_reg(quReg *qr, int *idxs);

// Quantum Swap Gate
// Swaps the two qubits
// For two different qubits
void QSwap(quBit *x1, quBit *x2);

// For register of qubits
quReg* QSwap_reg(quReg *qr, int idx1, int idx2);

// Quantum Fourier Transform Gate
quReg* QFT_reg(quReg *qr, int *idxs);

// Inverse Quantum Fourier Transform Gate
quReg* Inv_QFT_reg(quReg *qr, int *idxs);

// Function Definitions
//
//
//
//
//

quBit X(quBit x) {
	quBit qb = newQubit(0);

	qb.ZCoeff.real = x.OCoeff.real;
	qb.ZCoeff.imag = x.OCoeff.imag;
	
	qb.OCoeff.real = x.ZCoeff.real;
	qb.OCoeff.imag = x.ZCoeff.imag;

	return qb;
}

quReg* X_reg(quReg *qr, int idx) {
	int prev_state = -1, next_state = -1;
	int i, size = pow(2, qr->size);

	qr->qb[idx] = X(qr->qb[idx]);

	for(i = 0; i < size; i++) {
		if((i & (1 << idx)) == 0) {
			prev_state = i;
			next_state = prev_state ^ (1 << idx);

			Complex temp = qr->matrix[prev_state];
			qr->matrix[prev_state] = qr->matrix[next_state];
			qr->matrix[next_state] = temp;
		}
	}

	return qr;
}

quBit Z(quBit x) {
	quBit qb = newQubit(0);

	qb.ZCoeff = x.ZCoeff;

	qb.OCoeff.real = x.OCoeff.real;
	qb.OCoeff.imag = -1 * x.OCoeff.imag;

	return qb;
}

quReg* Z_reg(quReg *qr, int idx) {
	int i, size = pow(2, qr->size);

	qr->qb[idx] = Z(qr->qb[idx]);

	for(i = 0; i < size; i++) {
		if((i & (1 << idx)) > 0) {
			qr->matrix[i].real *= -1;
			qr->matrix[i].imag *= -1;
		}
	}

	return qr;
}

quBit Y(quBit x) {
	quBit qb = newQubit(0);

	qb.ZCoeff.real = x.OCoeff.imag;
	qb.ZCoeff.imag = -1 * x.OCoeff.real;

	qb.OCoeff.real = -1 * x.ZCoeff.imag;
	qb.OCoeff.imag = x.ZCoeff.real;

	return qb;
}

quReg* Y_reg(quReg *qr, int idx) {
	int prev_state = 0, next_state = 0;
	int i, size = pow(2, qr->size);

	qr->qb[idx] = Y(qr->qb[idx]);

	for(i = 0; i < size; i++) {
		if((i & (1 << idx)) == 0) {
			prev_state = i;
			next_state = prev_state ^ (1 << idx);

			Complex temp_ps = {qr->matrix[next_state].imag, -1 * qr->matrix[next_state].real};
			Complex temp_ns = {-1 * qr->matrix[prev_state].imag, qr->matrix[prev_state].real};

			qr->matrix[prev_state] = temp_ps;
			qr->matrix[next_state] = temp_ns;
		}
	}

	return qr;
}

quBit S(quBit x) {
	quBit qb = newQubit(0);

	qb.ZCoeff = x.ZCoeff;

	qb.OCoeff.real = -1 * x.OCoeff.imag;
	qb.OCoeff.imag = x.OCoeff.real;

	return qb;
}

quReg* S_reg(quReg *qr, int idx) {
	qr->qb[idx] = S(qr->qb[idx]);

	int size = pow(2, qr->size);

	for(int i = 0; i < size; i++) {
		if(i & (1 << idx)) {
			double temp = qr->matrix[i].real;
			qr->matrix[i].real = -1 * qr->matrix[i].imag;
			qr->matrix[i].imag = temp;
		}
	}

	return qr;
}

quBit R(double angle, quBit x) {
	quBit qb = newQubit(0);

	qb.ZCoeff = x.ZCoeff;

	qb.OCoeff.real = x.OCoeff.real * cos(angle) - x.OCoeff.imag * sin(angle);
	qb.OCoeff.imag = x.OCoeff.real * sin(angle) + x.OCoeff.imag * cos(angle);

	return qb;
}

quReg* R_reg(double angle_deg, quReg *qr, int idx) {
	int size = pow(2, qr->size);
	double angle_rad = angle_deg / 180 * PI;

	qr->qb[idx] = R(angle_rad, qr->qb[idx]);

	for(int i = 0; i < size; i++) {
		if(i & (1 << idx)) {
			double temp_real = qr->matrix[i].real;
			double temp_imag = qr->matrix[i].imag;
			qr->matrix[i].real = temp_real * cos(angle_rad) - temp_imag * sin(angle_rad);
			qr->matrix[i].imag = temp_real * sin(angle_rad) + temp_imag * cos(angle_rad);
		}
	}

	return qr;
}

quBit H(quBit x) {
	quBit qb = newQubit(0);

	qb.ZCoeff.real = (x.ZCoeff.real + x.OCoeff.real) / sqrt(2);
	qb.OCoeff.real = (x.ZCoeff.real - x.OCoeff.real) / sqrt(2);

	qb.ZCoeff.imag = (x.ZCoeff.imag + x.OCoeff.imag) / sqrt(2);
	qb.ZCoeff.imag = (x.ZCoeff.imag - x.OCoeff.imag) / sqrt(2);

	return qb;
}

void Hadamard(quReg *qr, int first, int second) {
	double temp_ps_real, temp_ns_real, temp_ps_imag, temp_ns_imag;

	temp_ps_real = qr->matrix[first].real;
	temp_ps_imag = qr->matrix[first].imag;

	temp_ns_real = qr->matrix[second].real;
	temp_ns_imag = qr->matrix[second].imag;
	
	qr->matrix[first].real = (temp_ps_real + temp_ns_real) / sqrt(2);
	qr->matrix[second].real = (temp_ps_real - temp_ns_real) / sqrt(2);

	qr->matrix[first].imag = (temp_ps_imag + temp_ns_imag) / sqrt(2);
	qr->matrix[second].imag = (temp_ps_imag - temp_ns_imag) / sqrt(2);
}

quReg* H_reg(quReg *qr, int idx) {
	qr->qb[idx] = H(qr->qb[idx]);

	const int mat_size = pow(2, qr->size);
	bool *visited = (bool*) malloc(mat_size * sizeof(bool));

	for(int i = 0; i < mat_size; i++)
		visited[i] = false;

	int first, second;

	for(int i = 0; i < mat_size; i++) {
		if(!visited[i]) {
			first = i;
			second = i ^ (1 << idx);
			visited[first] = visited[second] = true;
			Hadamard(qr, first, second);
		}
	}

	return qr;
}

void CNOT(quBit *x1, quBit *x2) {
	quBit qb = newQubit(0);

	if(__round(fabs(x1->OCoeff.real)) > 0 || __round(fabs(x1->OCoeff.imag)) > 0)
		qb = X(*x2);

	*x2 = qb;
}

quReg* CNOT_reg(quReg *qr, int *idxs) {
	const int mat_size = pow(2, qr->size);
	bool *visited = (bool*) malloc(mat_size * sizeof(bool));
	int first, second;

	for(int i = 0; i < mat_size; i++)
		visited[i] = false;

	int ctrl;
	for(int i = 0; i < qr->size; i++) {
		if(idxs[i] == -1) {
			ctrl = i;
			break;
		}
	}

	bool invert = false;

	for(int i = 0; i < mat_size; i++) {
		if((i & (1 << ctrl)) && (__round(fabs(qr->matrix[i].real)) > 0 || __round(fabs(qr->matrix[i].imag)) > 0)) {
			invert = true;
		}

		if(invert) {
			first = second = i;
			for(int j = 0; j < qr->size; j++) {
				if(idxs[j] == 1) {
					CNOT(&qr->qb[ctrl], &qr->qb[j]);
					second = second ^ (1 << j);
				}
			}

			if(!visited[first] && !visited[second]) {
				visited[first] = visited[second] = true;

				Complex temp = qr->matrix[first];
				qr->matrix[first] = qr->matrix[second];
				qr->matrix[second] = temp;
			}
		}

		invert = false;
	}



	return qr;
}

void QSwap(quBit *x1, quBit *x2) {
	quBit temp = *x1;
	*x1 = *x2;
	*x2 = temp;
}

quReg* QSwap_reg(quReg *qr, int idx1, int idx2) {
	QSwap(&qr->qb[idx1], &qr->qb[idx2]);

	const int mat_size = pow(2, qr->size);
	bool *visited = (bool*) malloc(mat_size * sizeof(bool));
	int state1, state2;
	int first, second;

	for(int i = 0; i < mat_size; i++)
		visited[i] = false;

	for(int i = 0; i < mat_size; i++) {
		if(!visited[i]) {
			state1 = (i & (1 << idx1)) >> idx1;
			state2 = (i & (1 << idx2)) >> idx2;
			first = i;
			second = (i ^ (1 << idx1)) ^ (1 << idx2);
			visited[first] = visited[second] = true;

			if(state1 != state2) {
				Complex temp = qr->matrix[first];
				qr->matrix[first] = qr->matrix[second];
				qr->matrix[second] = temp;
			}
		}
	}

	return qr;
}

quReg* QFT_reg(quReg *qr, int *idxs) {
	return qr;
}

quReg* Inv_QFT_reg(quReg *qr, int *idxs) {
	return qr;
}

#endif
