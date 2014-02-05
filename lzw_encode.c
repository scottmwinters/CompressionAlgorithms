#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_STRING_LENGTH 256

typedef struct entry_tag {
	unsigned char *seq;
	int val;
	struct entry_tag *fwd;
} entry;

entry *head = NULL;
entry *tail = NULL;

/*
	-1 = Not Found
	# = Position in Table
*/
int lookup_entry(unsigned char *seq) {

	if(head == NULL) return -1;

	entry *rover = head;

	do {
		printf("%d: %s\n", rover->val, rover->seq);
		
		if(rover->fwd != NULL) rover = rover->fwd;

	} while(rover->fwd != NULL);

	return rover->val;
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

int get_next_val() {
	if(tail == NULL) return 0;
	else return tail->val + 1;
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

	// Build Initial Single Bytes Table
	for(int i = 0; i < 256; i++)
		add_entry((unsigned char *) &i);

	// unsigned char *string = NULL;
	// unsigned char *current = NULL;
	// int strLen = 1;

 //  string = calloc(sizeof(*string), strLen); // 1
	// current = calloc(sizeof(*current), 1); // 2

	// fread(string, sizeof(*string), strLen, fpIn);

	// fread(current, sizeof(*current), 1, fpIn);

	// unsigned char *temp = calloc(sizeof(*temp), strLen + 1);

	// // s + w
	// for(int i = 0; i < strLen; i++) {
	// 	temp[i] = string[i];
	// }
	// temp[strLen] = current[0];

	// printf("%s\n", temp);

	// if(lookup_entry(temp) == -1 /* 3 */ ) {
		
	// 	int nxtVal = get_next_val();
	// 	fwrite(&nxtVal, sizeof(nxtVal), 1, fpOut);
		
	// 	add_entry(temp); // 5
	// }

	fclose(fpIn);
	fclose(fpOut);

	return 0;
}
