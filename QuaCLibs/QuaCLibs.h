#ifndef QUACLIBS_H

#define QUACLIBS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct complex {
	double real, imag;
}Complex;

typedef struct qb {
	Complex ZCoeff, OCoeff;
}quBit;

typedef struct qr {
	quBit *qb;
	unsigned short size;
	Complex *matrix;
}quReg;

char *format_str;

#define CHECK(test) ((test) ? 0:1)
#define PI M_PI

double __round(double num);
void print(quBit x);
void Qprint(const char* format, ...);
void setPrecision(int prec);

#include "QuaCMemAlloc.h"
#include "QuaCGates.h"
#include "HashMap.h"
#include "Types.h"
#include "QuaCLexer.h"
#include "QuaCParser.h"
#include "QuaCExecutor.h"

// Custom round function so as to take care of significant digits after decimal place.
double __round(double num) {
	int threshold = 1000000;
	return (round(num * threshold) / threshold);
}

double mag(quReg *qr, int i) {
	double mod = sqrt(pow(qr->matrix[i].real, 2) + pow(qr->matrix[i].imag, 2));
    return (pow(mod, 2) * 100);
}

void print(quBit x) {
	int flag0 = 0, flag1 = 0;

	if(__round(x.ZCoeff.real) != 0 || __round(x.ZCoeff.imag) != 0) {
		if(__round(x.ZCoeff.real) == 0)
			printf("{");
		else if(__round(x.ZCoeff.real) == 1) {
			printf("1");
			flag0 = 1;
		}
		else
			printf("{%f", x.ZCoeff.real);

		if(x.ZCoeff.imag > 0 && __round(x.OCoeff.real) != 0)
			printf(" + ");
		else if(x.ZCoeff.imag < 0 && __round(x.OCoeff.real) != 0)
			printf(" - ");

		if(__round(x.ZCoeff.imag) == 0) {
			if(flag0 == 0) {
				printf("}");
			}
		}
		else if(__round(x.ZCoeff.imag) == 1)
			printf("i}");
		else
			printf("%f i}", fabs(x.ZCoeff.imag));

		printf(" |0>");
	}

	if((__round(x.ZCoeff.real) == 0 && __round(x.ZCoeff.imag) == 0) || (__round(x.OCoeff.real) == 0 && __round(x.OCoeff.imag) == 0)) {

	} else {
		printf(" + ");
	}

	if(x.OCoeff.real != 0 || x.OCoeff.imag != 0) {
		if(__round(x.OCoeff.real) == 0)
			printf("{");
		else if(__round(x.OCoeff.real) == 1) {
			printf("1");
			flag1 = 1;
		}
		else
			printf("{%f", x.OCoeff.real);

		if(x.OCoeff.imag > 0 && __round(x.OCoeff.real) != 0)
			printf(" + ");
		else if(x.OCoeff.imag < 0 && __round(x.OCoeff.real) != 0)
			printf(" - ");

		if(__round(x.OCoeff.imag) == 0) {
			if(flag1 == 0) {
				printf("}");
			}
		}
		else if(__round(x.OCoeff.imag) == 1)
			printf("i}");
		else
			printf("%f i}", fabs(x.OCoeff.imag));

		printf(" |1>");
	}
}

void setPrecision(int prec) {
	int temp1, temp2;
	if(prec > 12)
		temp1 = 12;
	else
		temp1 = prec;

	temp2 = temp1;
	int count = 0;
	char *precision;

	while(temp2 != 0) {
		temp2 /= 10;
		count++;
	}

	precision = (char*) malloc((count + 3) * sizeof(char));
	precision[0] = '0';
	precision[1] = '.';
	precision[count + 2] = '\0';
	
	while(count > 0) {
		precision[1 + count] = (temp1 % 10) + '0';
		temp1 /= 10;
		count--;
	}

	char *format = (char*) malloc(25 * sizeof(char));

	strcat(format, "\t%");
	strcat(format, precision);
	strcat(format, "lf %%");

	format_str = format;
}

void Qprint(const char* format, ...) {
	const char *traverse;
    quBit qb;
    quBit *qr;
    quReg *QR;
    int i = 0;

    char buffer[33];

    //Module 1: Initializing Qprint's arguments 
    va_list arg;
    va_start(arg, format);

    for(traverse = format; CHECK(*traverse == '\n' || *traverse == '\0'); traverse++) {
        while( *traverse != '%') {
            putchar(*traverse);
            traverse++;
        }
        traverse++;

        //Module 2: Fetching and executing arguments
        switch(*traverse) {
            case 'q': qb = va_arg(arg, quBit);
            		  print(qb);
            		  break;

            case 'r': QR = va_arg(arg, quReg*);
            		  for(i = 0; i < pow(2, QR->size); i++) {
            		  	if(fabs(__round(QR->matrix[i].real)) > 0 || fabs(__round(QR->matrix[i].imag)) > 0) {
	        		  		printf("\n[%d] =>\t{%lf", i, __round(QR->matrix[i].real));
	        		  		if(QR->matrix[i].imag < 0)
	        		  			printf(" - ");
	        		  		else
	        		  			printf(" + ");
	        		  		printf("%lf i} |", fabs(__round(QR->matrix[i].imag)));
	        		  		for(int j = 0; j < QR->size; j++) {
	        		  			int b = (i & (1 << (QR->size - j - 1))) >> (QR->size - j - 1);
	        		  			printf("%d", b);
	        		  		}
	        		  		printf(">");

	        		  		printf(format_str, mag(QR, i));
	        		  	}
            		  }
            		  printf("\n");
            		  break;

            case 'a': QR = va_arg(arg, quReg*);
            		  for(i = 0; i < pow(2, QR->size); i++) {
        		  		printf("\n[%d] =>\t{%lf", i, __round(QR->matrix[i].real));
        		  		if(QR->matrix[i].imag < 0)
        		  			printf(" - ");
        		  		else
        		  			printf(" + ");
        		  		printf("%lf i} |", fabs(__round(QR->matrix[i].imag)));
        		  		for(int j = 0; j < QR->size; j++) {
        		  			int b = (i & (1 << (QR->size - j - 1))) >> (QR->size - j - 1);
        		  			printf("%d", b);
        		  		}
        		  		printf(">");

        		  		printf(format_str, mag(QR, i));
            		  }
            		  printf("\n");
            		  break;
        }
    }

    putchar(*traverse);
    putchar(*traverse);

    //Module 3: Closing argument list to necessary clean-up
    va_end(arg); 
}

#endif
