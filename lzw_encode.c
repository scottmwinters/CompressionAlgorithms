#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

#define MAX_STRING_LENGTH 256
#define VAL_TYPE unsigned int

typedef struct entry_tag {
	unsigned char *seq;
	VAL_TYPE val;
	struct entry_tag *fwd;
} entry;

entry *head = NULL;
entry *tail = NULL;

// -1 = Not Found
VAL_TYPE lookup_entry(unsigned char *seq, int strLen) {

	if(head == NULL) return -1;

	entry *rover = head;

	do {
		if(memcmp(rover->seq, seq, strLen) == 0) return rover->val;
		if(rover->fwd != NULL) rover = rover->fwd;
	} while(rover->fwd != NULL);

	return -1;
}

void add_entry(unsigned char *seq) {

	entry *newEntry = calloc(sizeof(entry), 1);

	newEntry->seq = seq;
	newEntry->fwd = NULL;

	if(head == NULL) {
		newEntry->val = 0;
		head = newEntry;
	}	

	if(tail == NULL)
		tail = newEntry;
	else {
		newEntry->val = tail->val + 1;
		tail->fwd = newEntry;
		tail = newEntry;
	}

}

int main(int argc, char **argv) {

	assert(argc == 2);

	FILE *fpIn = NULL;
	FILE *fpOut = NULL;

	fpIn = fopen(argv[1], "rb");

	char outputFile[MAX_STRING_LENGTH];
	strcpy(outputFile, argv[1]);
	strcat(outputFile, ".lzw");

	fpOut = fopen(outputFile, "wb");

	assert(fpIn != NULL);
	assert(fpOut != NULL);

	// Build Initial Single Byte Table (0 - 255)
	for(int i = 0; i < 256; i++) {
		unsigned char *temp = calloc(sizeof(*temp), 1);
		memcpy(temp, (unsigned char *)&i, 1);
		add_entry(temp);
	}
		
	unsigned char *string = NULL;
	unsigned char *current = NULL;
	int strLen = 1;

  string = calloc(sizeof(*string), strLen); // 1
	current = calloc(sizeof(*current), 1); // 2

	fread(string, sizeof(*string), strLen, fpIn);

	while(fread(current, sizeof(*current), 1, fpIn) /* 8 */) {

		unsigned char *temp = calloc(sizeof(*temp), strLen + 1);

		// s + w
		for(int i = 0; i < strLen; i++) {
			temp[i] = string[i];
		}
		temp[strLen] = current[0];

		if(lookup_entry(temp, strLen + 1) == -1 /* 3 */ ) {
		
			VAL_TYPE stringVal = lookup_entry(string, strLen);
			fwrite(&stringVal, sizeof(stringVal), 1, fpOut); // 4

			add_entry(temp); // 5

			free(string);
			string = NULL;

			strLen = 1;
			string = calloc(sizeof(*string), strLen);
			string = current; // 6


		} else {
			
			strLen++;

			free(string);
			string = temp; // 7
		}

		current = calloc(sizeof(*current), 1); // 2s
	};


	VAL_TYPE stringVal = lookup_entry(string, strLen);
	fwrite(&stringVal, sizeof(stringVal), 1, fpOut); // 9

	fclose(fpIn);
	fclose(fpOut);

	return 0;
}
