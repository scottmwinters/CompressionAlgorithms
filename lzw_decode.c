#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

#define MAX_STRING_LENGTH 256
#define VAL_TYPE short int

typedef struct entry_tag {
	unsigned char *seq;
	VAL_TYPE val;
	int strLen;
	struct entry_tag *fwd;
} entry;

entry *head = NULL;
entry *tail = NULL;


void print_list() {

	entry *rover = head;
	do {
		printf("%d : ", rover->val);
		for(int i = 0; i < rover->strLen; i++)
			printf("%x", rover->seq[i]);

		printf("\n");

		rover = rover->fwd;
	} while(rover != NULL);
}

void print_string(unsigned char *str, int strLen) {
	for(int i = 0; i < strLen; i++)
		printf("%x", str[i]);

	printf("\n");
}

// NULL = Not Found
entry *lookup_by_val(VAL_TYPE val) {

	if(head == NULL) return NULL;

	entry *rover = head;

	do {
		if(rover->val == val) return rover;
		rover = rover->fwd;
	} while(rover != NULL);

	return NULL;
}

void add_entry(unsigned char *seq, int strLen) {

	entry *newEntry = calloc(sizeof(entry), 1);

	newEntry->seq = seq;
	newEntry->fwd = NULL;
	newEntry->strLen = strLen;

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

	// Build Initial Single Byte Table (0 - 255)
	for(unsigned int i = 0; i < 256; i++) {
		unsigned char *temp = calloc(sizeof(*temp), 1);
		memcpy(temp, (unsigned char *)&i, 1);
		add_entry(temp, 1);
	}

	VAL_TYPE current = -1;
	VAL_TYPE previous = -1;

	entry *currentEntry = NULL;
	entry *previousEntry = NULL;

	fread(&current, sizeof(current), 1, fpIn);
	currentEntry = lookup_by_val(current);
	fwrite(currentEntry->seq, sizeof(*currentEntry->seq), currentEntry->strLen, fpOut);

	previous = current;

	while(fread(&current, sizeof(current), 1, fpIn)) {

		currentEntry = lookup_by_val(current);

		if(currentEntry == NULL) {

			previousEntry = lookup_by_val(previous);

			unsigned char *temp = calloc(sizeof(*temp), previousEntry->strLen + 1);
			memcpy(temp, previousEntry->seq, previousEntry->strLen);
			temp[previousEntry->strLen] = previousEntry->seq[0];

			fwrite(temp, sizeof(*temp), previousEntry->strLen + 1, fpOut);

			add_entry(temp, previousEntry->strLen + 1);

		} else {

			fwrite(currentEntry->seq, sizeof(*currentEntry->seq), currentEntry->strLen, fpOut);

			previousEntry = lookup_by_val(previous);

			unsigned char *temp = calloc(sizeof(*temp), previousEntry->strLen + 1);
			memcpy(temp, previousEntry->seq, previousEntry->strLen);
			temp[previousEntry->strLen] = currentEntry->seq[0];

			add_entry(temp, previousEntry->strLen + 1);
		}

		previous = current;

	}

	

	fclose(fpIn);
	fclose(fpOut);

	return 0;
}
