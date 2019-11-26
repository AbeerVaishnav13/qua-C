#include "QuaCLibs/QuaCLibs.h"
#include <sys/time.h>

int main(int argc, char *argv[]) {
	FILE *fp;
	struct timeval start, end;
	int l = strlen(argv[1]);

	if(argv[1][l-1] == 'c' && argv[1][l-2] == 'q' && argv[1][l-3] == '.') {
		fp = fopen(argv[1], "r");
		HashMap *hm;
		bool correct = false;
		bool parse_success = false;

		hm = Tokenize(fp);

		input = toArrayofTypes(*hm);
		parse_success = Parse();

		if(parse_success) {
			printf("\n[+] Parsing Successful...!!!\n\n");
		}
		else {
			printf("\n[!] Code Rejected due to syntax error...\n\n");
			exit(-1);
		}

		gettimeofday(&start, NULL);
		RunProgram(toArrayOfKeyTypes(*hm));
		gettimeofday(&end, NULL);

		double timeTaken = (end.tv_sec - start.tv_sec) * 1e6;
		timeTaken = (timeTaken + (end.tv_usec - start.tv_usec)) * 1e-6;

		int min = timeTaken / 60;
		double sec = (double)((int)timeTaken % 60);
		sec += (timeTaken - (min * 60 + sec));

		printf("\n\nTime taken: %d min, %lf sec\n", min, sec);

		free(input);
		free(hm);
	}
	else {
		printf("Please input a valid file with '.qc' extension...\n");
	}

	return 0;
}