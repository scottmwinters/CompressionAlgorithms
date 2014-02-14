#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_STRING_LENGTH 256

int main(int argc, char **argv) {

	assert(argc == 2);

	FILE *fpIn = NULL;
	FILE *fpOut = NULL;

	fpIn = fopen(argv[1], "rb");

	char outputFile[MAX_STRING_LENGTH];
	strcpy(outputFile, argv[1]);
	strcat(outputFile, ".rle");

	fpOut = fopen(outputFile, "wb");

	unsigned char current = 0;
	unsigned char previous = 0;

	unsigned int counter = 0;

	fread(&previous, sizeof(previous), 1, fpIn);

	while(1 == fread(&current, sizeof(current), 1, fpIn)) {

		if(current == previous) {
			counter++;
			if(counter == 4294967295) {
				printf("Error: Going to overflow. Exiting\n");
				exit(1);
			} 
		}
		else {
		  fwrite(&counter, sizeof(counter), 1, fpOut);
		  fwrite(&previous, sizeof(previous), 1, fpOut);
			counter = 0;
		}

		previous = current;
	}

	fwrite(&counter, sizeof(counter), 1, fpOut);
	fwrite(&current, sizeof(current), 1, fpOut);

	fclose(fpIn);
	fclose(fpOut);

	return 0;
}
