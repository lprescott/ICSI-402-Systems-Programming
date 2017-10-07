#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "headersOne.h"

/*
	Function logline* parseLine(string line) to construct a logline with 3 elds
	based on the input string. Note that this function allocates memory.

	Must check if inputted char line [] has atleast two commas, and print to
	stderr if not.
	
	Must check if log entry looks like <level>,<timestamp>,<message>,
	and print to stderr if not.
*/
logline_t * parseLine(char line []){
	char str[128];
	strcpy(str, line);

	char * levelP = strtok(str, ",");
	char * timestampP = strtok(NULL, ",");
	char * messageP = strtok(NULL, ",");

	logline_t * parsed = NULL;
	if((parsed = malloc(sizeof(logline_t))) == NULL){
		fprintf(stderr, "Unable to allocate memory for new parsed structure.\n");
		exit(-1);
	}

	strcpy(parsed->level , levelP);
	strcpy(parsed->timestamp , timestampP);
	strcpy(parsed->message , messageP);

	return parsed;
}

/*
	Function void deleteList(loglist* l) to free all memory allocated for the list.
*/
void deleteList(loglist_t * l){
	
}

/*
	Function void printLines(LineList* l) to print all the lines contained in the list.
*/
void printLines(loglist_t * l){
	
} 
