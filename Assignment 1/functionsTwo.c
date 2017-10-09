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
	loglist_t * current = inlist, * current2 = inlist->next, * temp;
	while(current->next->next != NULL){
			if((strcmp(current->line.timestamp, current2->line.timestamp)) < 0){
					temp = current;
					current = current2;
					current2 = temp;
			}
			current = current->next;
	}
	current->next = NULL;
}
