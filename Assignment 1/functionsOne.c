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
	loglist_t * next;
	char levelTemp[100];
	char timestampTemp[100];
	char messageTemp[100];

	//sets all things to their temp things
	strcpy(levelTemp, head->line.level);
	strcpy(timestampTemp, head->line.timestamp);
	strcpy(messageTemp, head->line.message);

	//prints the data elements of the head, which include the level, message, and the timestamp
	printf("%s,%s,%s", levelTemp, timestampTemp, messageTemp);

	// repeats the same process, but for the rest of the linked list.
	while (head->next != NULL) {
		strcpy(levelTemp, head->next->line.level);
		strcpy(timestampTemp, head->next->line.timestamp);
		strcpy(messageTemp, head->next->line.message);

		if((strstr(levelTemp, "(")) !=  NULL || (strstr(timestampTemp, "(")) !=  NULL || (strstr(messageTemp, "(")) !=  NULL ){
			continue;
		}
		printf("%s,%s,%s", levelTemp, timestampTemp, messageTemp);

		head->next = head->next->next;// traversing the linked list.
	
	}
}
