#include "Includes.h"

FILE *fp;
FILE *fp2;

int main(int argc, char *argv[]) {
	fp = fopen(argv[1], "r");
	HashMap *hm;
	bool correct = false;

	hm = Tokenize(fp);

	correct = syntaxCheck(hm);

	if(correct)
		printf("\nSyntax is correct!");
	else
		printf("\nSyntax not correct...");

	return 0;
}