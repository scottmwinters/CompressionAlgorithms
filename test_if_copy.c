#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_STRING_LENGTH 256

int main(int argc, char **argv) {

	FILE *fp1 = NULL;
	FILE *fp2 = NULL;

	assert(argc == 3);

	fp1 = fopen(argv[1], "rb");
	fp2 = fopen(argv[2], "rb");

	assert(fp1 != NULL);
	assert(fp2 != NULL);

	unsigned char file1Input, file2Input;

	while(fread(&file1Input, sizeof(file1Input), 1, fp1) == fread(&file2Input, sizeof(file2Input), 1, fp2)) {
		if(file1Input != file2Input) {
			printf("Test Failed - %s is not a copy of %s\n", argv[1], argv[2]);
			exit(1);
		}
	}

	printf("Test Passed - %s is a copy of %s\n", argv[1], argv[2]);

	return 0;
}
