#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "headersOne.h"

/*
	Function logline* parseLine(string line) to construct a logline with 3 elds
	based on the input string. Note that this function allocates memory.
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
void deleteList(loglist_t * head){
	if (head == NULL){
		return;
	}

	loglist_t * current = head;
	loglist_t * next;

	while (current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}
	head = NULL;
}

/*
	Function void printLines(LineList* l) to print all the lines contained in the list.
*/
void printLines( loglist_t * head){

	if (head == NULL){
		printf("Empty List\n");
		return;
	}
	//initalizes all the temp variables
	loglist_t * temp;
	temp = head;
	//prints the data elements of the head, which include the level, message, and the timestamp
	printf("%s,%s,%s", temp->line.level, temp->line.timestamp, temp->line.message);
	// repeats the same process, but for the rest of the linked list.
	while(temp!=NULL)
    {
    	printf("%s,%s,%s", temp->line.level, temp->line.timestamp, temp->line.message);
    	temp=temp->next;
    }
}
