#ifndef QUANTUMMEMALLOC_H

#define QUANTUMMEMALLOC_H

// Declaring a new Qubit.
quBit newQubit(int init_state);

// Declaring a new Qubit Register with 'n' Qubits.
quReg* newQuReg(size_t n);



// Function Definitions
//
//
//
//

quBit newQubit(int init_state) {
	quBit qb;

	if(init_state == 0) {
		qb.ZCoeff.real = 1.0;
		qb.OCoeff.real = 0.0;
		qb.ZCoeff.imag = qb.OCoeff.imag = 0.0;
	} else if(init_state == 1) {
		qb.ZCoeff.real = 0.0;
		qb.OCoeff.real = 1.0;
		qb.ZCoeff.imag = qb.OCoeff.imag = 0.0;
	} else {
		printf("ERROR: Invalid initial state value. It can either be |0> or |1>.\n");
		exit(0);
	}
	
	return qb;
}

quReg* newQuReg(size_t n) {
	quReg *qr = (quReg*) malloc(sizeof(quReg));

	qr->qb = (quBit*) malloc((n+1) * sizeof(quBit));

	qr->size = n;

	for(int i = 0; i <= n; i++) {
		qr->qb[i] = newQubit(0);
		if(i == n) {
			qr->qb[i].ZCoeff.real = qr->qb[i].OCoeff.real = 0;
			qr->qb[i].ZCoeff.imag = qr->qb[i].OCoeff.imag = 0;
		}
	}

	qr->matrix = (Complex*) malloc(pow(2, n) * sizeof(Complex));
	qr->matrix[0].real = 1; qr->matrix[0].imag = 0;

	for(int i = 1; i < pow(2, n); i++) {
		qr->matrix[i].real = qr->matrix[i].imag = 0;
	}

	setPrecision(2);

	return qr;
}

#endif