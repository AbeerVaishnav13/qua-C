#include "QuaCLibs/QuaCLibs.h"

int main(int argc, char const *argv[]) {

	FILE *fp;

	int l = strlen(argv[1]);

	if(argv[1][l-1] == 'c' && argv[1][l-2] == 'q' && argv[1][l-3] == '.') {
		fp = fopen(argv[1], "r");
		apply_Program(fp);
	}
	else {
		printf("Please input a valid file with '.qc' extension...\n");
	}

	return 0;
}