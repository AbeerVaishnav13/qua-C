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
// Rotates the Coefficient of Quantum state about any Axis (X, Y, or Z).
// angle should be in PI/k format, where k = 1, 2, 3, ...
// For single qubit
quBit Rx(double angle, quBit x);

// For register of qubits
quReg* Rx_reg(double angle, quReg *qr, int idx);

// For single qubit
quBit Ry(double angle, quBit x);

// For register of qubits
quReg* Ry_reg(double angle, quReg *qr, int idx);

// For single qubit
quBit Rz(double angle, quBit x);

// For register of qubits
quReg* Rz_reg(double angle, quReg *qr, int idx);

// Quantum CNOT Gate (Controlled NOT):-
// if (x1 == |1>) {x2 = X(x2)}
// else {x2 = x2}
// "Generally used for entanglement of the Qubits x1 and x2".
// For two different qubits
void CNOT(quBit *x1, quBit *x2);

// For register of qubits
quReg* CNOT_reg(quReg *qr, int idx1, int idx2);

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

Complex multiply_complex(Complex num1, Complex num2) {
	Complex temp;
	temp.real = num1.real * num2.real - num1.imag * num2.imag;
	temp.imag = num1.real * num2.imag + num1.imag * num2.real;
	return temp;
}

quReg* update_matrix(quReg *qr) {
	unsigned int mat_size = pow(2, qr->size);
	int i, j;

	for(i = 0; i < mat_size; i++) {
		Complex probab = {1, 1};
		for(j = 0; j < qr->size; j++) {
			if(j == 0) {
				if(i & (0x1 << j)) {
					probab = qr->qb[j].OCoeff;
				}
				else {
					probab = qr->qb[j].ZCoeff;
				}
			}
			else {
				if(i & (0x1 << j)) {
					probab = multiply_complex(probab, qr->qb[j].OCoeff);
				}
				else {
					probab = multiply_complex(probab, qr->qb[j].ZCoeff);
				}
			}
		}
		qr->matrix[i].real = probab.real;
		qr->matrix[i].imag = probab.imag;
	}
	return qr;
}

quBit X(quBit x) {
	quBit qb = newQubit(0);

	qb.ZCoeff.real = x.OCoeff.real;
	qb.ZCoeff.imag = x.OCoeff.imag;
	
	qb.OCoeff.real = x.ZCoeff.real;
	qb.OCoeff.imag = x.ZCoeff.imag;

	return qb;
}

quReg* X_reg(quReg *qr, int idx) {
	qr->qb[idx] = X(qr->qb[idx]);
	return update_matrix(qr);
}

quBit Z(quBit x) {
	quBit qb = newQubit(0);

	qb.ZCoeff = x.ZCoeff;

	qb.OCoeff.real = x.OCoeff.real;
	qb.OCoeff.imag = -1 * x.OCoeff.imag;

	return qb;
}

quReg* Z_reg(quReg *qr, int idx) {
	qr->qb[idx] = Z(qr->qb[idx]);
	return update_matrix(qr);
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
	qr->qb[idx] = Y(qr->qb[idx]);
	return update_matrix(qr);
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
	return update_matrix(qr);
}

quBit Rx(double angle, quBit x) {
	quBit qb = newQubit(0);

	qb.ZCoeff.real = x.ZCoeff.real * cos(angle) + x.OCoeff.imag * sin(angle);
	qb.ZCoeff.imag = x.ZCoeff.imag * cos(angle) - x.OCoeff.real * sin(angle);

	qb.OCoeff.real = x.ZCoeff.imag * sin(angle) + x.OCoeff.real * cos(angle);
	qb.OCoeff.imag = -x.ZCoeff.real * sin(angle) + x.OCoeff.real * cos(angle);

	return qb;
}

quReg* Rx_reg(double angle, quReg *qr, int idx) {
	qr->qb[idx] = Rx(angle/2, qr->qb[idx]);
	return update_matrix(qr);
}

quBit Ry(double angle, quBit x) {
	quBit qb = newQubit(0);

	qb.ZCoeff.real = x.ZCoeff.real * cos(angle) - x.OCoeff.real * sin(angle);
	qb.ZCoeff.imag = x.ZCoeff.imag * cos(angle) - x.OCoeff.imag * sin(angle);

	qb.OCoeff.real = x.ZCoeff.real * sin(angle) + x.OCoeff.real * cos(angle);
	qb.OCoeff.imag = x.ZCoeff.imag * sin(angle) + x.OCoeff.imag * cos(angle);

	return qb;
}

quReg* Ry_reg(double angle, quReg *qr, int idx) {
	qr->qb[idx] = Ry(angle/2, qr->qb[idx]);
	return update_matrix(qr);
}

// TODO: Make changes
quBit Rz(double angle, quBit x) {
	quBit qb = newQubit(0);

	qb.ZCoeff.real = x.ZCoeff.real * cos(angle) + x.ZCoeff.imag * sin(angle);
	qb.ZCoeff.imag = x.ZCoeff.imag * cos(angle) - x.ZCoeff.real * sin(angle);

	qb.OCoeff.real = x.OCoeff.real * cos(angle) - x.OCoeff.imag * sin(angle);
	qb.OCoeff.imag = x.OCoeff.imag * cos(angle) + x.OCoeff.real * sin(angle);

	return qb;
}

quReg* Rz_reg(double angle, quReg *qr, int idx) {
	qr->qb[idx] = Rz(angle/2, qr->qb[idx]);
	return update_matrix(qr);
}

quBit H(quBit x) {
	quBit qb = newQubit(0);

	qb.ZCoeff.real = (x.ZCoeff.real + x.OCoeff.real) / sqrt(2);
	qb.OCoeff.real = (x.ZCoeff.real - x.OCoeff.real) / sqrt(2);

	qb.ZCoeff.imag = (x.ZCoeff.imag + x.OCoeff.imag) / sqrt(2);
	qb.ZCoeff.imag = (x.ZCoeff.imag - x.OCoeff.imag) / sqrt(2);

	return qb;
}

quReg* H_reg(quReg *qr, int idx) {
	qr->qb[idx] = H(qr->qb[idx]);
	return update_matrix(qr);
}

quReg* CNOT_reg(quReg *qr, int idx1, int idx2) {
	qr->qb[idx1].ZCoeff.real = qr->qb[idx1].ZCoeff.imag = qr->qb[idx1].OCoeff.real = qr->qb[idx1].OCoeff.imag = 0;
	qr->qb[idx2].ZCoeff.real = qr->qb[idx2].ZCoeff.imag = qr->qb[idx1].OCoeff.real = qr->qb[idx1].OCoeff.imag = 0;

	const int mat_size = pow(2, qr->size);
	bool *visited = (bool*) malloc(mat_size * sizeof(bool));
	int first, second;

	for(int i = 0; i < mat_size; i++)
		visited[i] = false;

	for(int i = 0; i < mat_size; i++) {
		if((i & (1 << idx1)) && (__round(fabs(qr->matrix[i].real)) > 0 || __round(fabs(qr->matrix[i].imag)) > 0)) {
			first = i;
			second = first ^ (1 << idx2);

			if(!visited[first] && !visited[second]) {
				visited[first] = visited[second] = true;

				Complex temp = qr->matrix[first];
				qr->matrix[first] = qr->matrix[second];
				qr->matrix[second] = temp;
			}
		}
	}
	return qr;
}

quReg* QSwap_reg(quReg *qr, int idx1, int idx2) {
	quBit temp = qr->qb[idx1];
	qr->qb[idx1] = qr->qb[idx2];
	qr->qb[idx2] = temp;

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
