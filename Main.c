#include "Includes.h"

FILE *fp;
FILE *fp2;

int main(int argc, char *argv[]) {
	fp = fopen(argv[1], "r");
	HashMap *hm;

	hm = scanFile(fp);

	printf("\n\n DISPLAY HASHMAP\n");
	displayMap(*hm);

	return 0;
}