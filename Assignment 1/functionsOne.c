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
	//Creates a duplicate string before tokenizing
	char str[128];
	strcpy(str, line);
	
	//tokenizes lines to name, time, and message
	char * levelP = strtok(str, ",");
	char * timestampP = strtok(NULL, ",");
	char * messageP = strtok(NULL, ",");
	
	//checks to make sure that line is free to be used
	logline_t * parsed = NULL;
	if((parsed = malloc(sizeof(logline_t))) == NULL){
		fprintf(stderr, "Unable to allocate memory for new parsed structure.\n");
		exit(-1);
	}
  	
	//if there is no end of line character, then it puts one on the end of the string
  	if (strstr(messageP, "\n") == NULL) {
   	 	strcat(messageP, "\n");
  	}
  	
	//copys the tokens onto the line struct
	strcpy(parsed->level , levelP);
	strcpy(parsed->timestamp , timestampP);
	strcpy(parsed->message , messageP);

	return parsed;
}

/*
	Function void deleteList(loglist* l) to free all memory allocated for the list.
*/
void deleteList(loglist_t * head){
	//if head is equal to null, then return
	if (head == NULL){
		return;
	}
	
	//sets current equal to head
	loglist_t * current = head;
	loglist_t * next;
	
	//loops through the list, freeing up data for every variable until current hits null
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
	
	//if head is equal to null, then it breaks
	if (head == NULL){
		printf("Empty List\n");
		return;
	}
	//initalizes all the temp variables
	loglist_t * temp = malloc(sizeof(loglist_t));
	if (temp == NULL){
		fprintf(stderr, "Unable to allocate memory for new temp structure.\n");
		exit(-1);
	}
	temp = head -> next;
	//prints the data elements of the head, which include the level, message, and the timestamp
	//printf("%s,%s,%s", temp->line.level, temp->line.timestamp, temp->line.message);
	// repeats the same process, but for the rest of the linked list.
	while(temp!=NULL)
    {
    	printf("%s,%s,%s", temp->line.level, temp->line.timestamp, temp->line.message);
      temp=temp->next;
    }
}
