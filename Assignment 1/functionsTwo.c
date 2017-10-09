#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "structs.h"
#include "headersTwo.h"
#include "headersOther.h"

/*
	Function loglist* mergeLists(loglist* resultlist, loglist* inlist) to merge
	sorted linked list inlist into resultlist and return a pointer to the head of the
	combined list.
*/
loglist_t * mergeLists(loglist_t * resultlist, loglist_t * inlist){

	loglist_t * temp;
	temp = inlist->next;

	/* Find the end of resultList */
	if (temp == NULL){
		return resultlist;
	}
	else{
		while(temp != NULL){
			logline_t * templine = malloc(sizeof(logline_t));
			if (templine == NULL){
				fprintf(stderr, "Unable to allocate memory for new temp line structure.\n");
				exit(-1);
			}
			* templine = temp->line;
			addLast(resultlist, * templine);
			temp = temp->next;
		}
	}

	/* Loop through inlist item by item, adding lines to resultList */

	return resultlist;
}

/*
	Function loglist* sortList(loglist* inlist) to sort the provided linked list inlist
	and return a pointer to the head of the sorted list.
*/
loglist_t * sortList(loglist_t * inlist) {
	if (inlist == NULL){
		printf("Empty List\n");
		return NULL;
	}

	//initalizes all the temp variables
	loglist_t * temp = malloc(sizeof(loglist_t));
	if (temp == NULL){
		fprintf(stderr, "Unable to allocate memory for new temp structure.\n");
		exit(-1);
	}
	temp = inlist -> next;

	do{
		int boolean = 0;
		while(temp!=NULL)
		{
			if(strcmp(temp->line.timestamp, temp->next->line.timestamp) > 0){
				swap(temp, temp->next);
			}
			temp = temp->next;
		}
	}

}
