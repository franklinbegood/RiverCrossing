#include "river.h"

int main(int argc, char **argv) {
	char *inputFileName = NULL;

	if(argc != 2) {
		fprintf(stderr, "Non-standard number of arguments.");
	} else {
		inputFileName = argv[1];
	}

	int fewest = fewestRotations(inputFileName);
	if(fewest < 0) {
		fprintf(stderr, "File i/o error.\n");
		return EXIT_SUCCESS;
	}
	
	printf("%d\n",fewest);	
	
	return EXIT_SUCCESS;
}
