#include <stdio.h>
#include <string.h>

#include "structs.h"
#include "headersTwo.h"
#include "headersOther.h"

/*
	Function loglist* mergeLists(loglist* resultlist, loglist* inlist) to merge
	sorted linked list inlist into resultlist and return a pointer to the head of the
	combined list.
*/
loglist_t * mergeLists(loglist_t * resultlist, loglist_t * inlist){

	loglist_t dummy;

	loglist_t * tail = &dummy;

	dummy.next = NULL;

	while (1) {
		if (resultlist == NULL) {
			tail->next = inlist;
			break;
		} else if (inlist == NULL) {
			tail->next = resultlist;
			break;
		}
		if (strcmp(resultlist->line.timestamp, inlist->line.timestamp) <= 0)
			moveNode(&(tail->next), &resultlist);
		else
			moveNode(&(tail->next), &inlist);

		tail = tail->next;
	}
	return (dummy.next);
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
