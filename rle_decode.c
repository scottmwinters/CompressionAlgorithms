#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_STRING_LENGTH 256

int main(int argc, char **argv) {

	assert(argc == 2);

	FILE *fpIn = NULL;
	FILE *fpOut = NULL;

	// Verify File is of Correct Type
	int strLen = strlen(argv[1]);
	
	char rleFileTag[MAX_STRING_LENGTH];
	strcpy(rleFileTag, argv[1] + strLen - 4);

	if(strcmp(rleFileTag, ".rle") != 0) {
		printf("Invalid File Type. Must be '.rle'\n");
		exit(1);
	}

	char outputFile[MAX_STRING_LENGTH];
	strncpy(outputFile, argv[1], strLen - 4);

	fpIn = fopen(argv[1], "rb");
	fpOut = fopen(outputFile, "wb");

	assert(fpIn != NULL);
	assert(fpOut != NULL);

	unsigned char current = 0;
	unsigned char counter = 0;

	while(fread(&counter, sizeof(counter), 1, fpIn)) {
		
		fread(&current, sizeof(current), 1, fpIn);

		for(int i = 0; i <= counter; i++)
			fwrite(&current, sizeof(current), 1, fpOut);
	}

	fclose(fpIn);
	fclose(fpOut);

	return 0;
}
