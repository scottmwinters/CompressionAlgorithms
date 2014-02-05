#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_STRING_LENGTH 256

int main(int argc, char **argv) {

	assert(argc == 2);

	FILE *fpIn = NULL;
	FILE *fpOut = NULL;

	int strLen = strlen(argv[1]);
	
	char rleFileTag[MAX_STRING_LENGTH];
	strcpy(rleFileTag, argv[1] + strLen - 4);

	if(strcmp(rleFileTag, ".lzw") != 0) {
		printf("Invalid File Type. Must be '.lzw'\n");
		exit(1);
	}

	char outputFile[MAX_STRING_LENGTH];
	strncpy(outputFile, argv[1], strLen - 4);

	fpIn = fopen(argv[1], "rb");
	fpOut = fopen(outputFile, "wb");

	assert(fpIn != NULL);
	assert(fpOut != NULL);

	fclose(fpIn);
	fclose(fpOut);

	return 0;
}
