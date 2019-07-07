#include "Includes.h"

FILE *fp1;
FILE *fp2;

int main(int argc, char *argv[]) {
	fp1 = fopen(argv[1], "r");
	HashMap *hm;
	bool correct = false;

	hm = Tokenize(fp1);

	printf("DISPLAY HASHMAP\n");
	displayMap(*hm);

	// Type *Tokens = toArrayofTypes(*hm);
	// int len = hm->len;

	// correct = syntaxCheck(Tokens, len);

	// if(correct)
	// 	printf("\nSyntax is correct!");
	// else
	// 	printf("\nSyntax not correct...");

	// exor_prods();

	return 0;
}