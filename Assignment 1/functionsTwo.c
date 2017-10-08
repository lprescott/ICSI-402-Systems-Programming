#include <stdio.h>
#include "structs.h"
#include "headersTwo.h"
#include "headersOther.h"

/*
	Function loglist* mergeLists(loglist* resultlist, loglist* inlist) to merge
	sorted linked list inlist into resultlist and return a pointer to the head of the
	combined list.
*/

//Nives node from the front of source to the front of dest.
//Before: Source = {1, 2, 3} Dest = {1, 2, 3}
//After: Source = {2, 3} Dest = {1, 1, 2, 3}
void moveNode(loglist_t ** dest, loglist_t ** source) {

	loglist_t *newnode = *source;

	*source = newnode->next;

	newnode->next = *dest;

	*dest = newnode;

}

loglist_t * mergeLists(loglist_t * resultlist, loglist_t * inlist){



}

/*
	Function loglist* sortList(loglist* inlist) to sort the provided linked list inlist
	and return a pointer to the head of the sorted list.
*/
/*
void sortedInsert(loglist_t ** inlist, loglist_t * newnode) {
  loglist_t * current;

  if ((*inlist == NULL) || (strcmp (*inlist->line.timestamp , newnode->line.timestamp) >= 0)) {
    newnode->next == inlist;
    *inlist = newnode;
  } else {
    current = *inlist;
    while (current->next != NULL && (strcmp (current->next->line.timestamp, newnode->line.timestamp) < 0)) {
      current = current->next;
    }
    newnode->next = current->next;
    current->next = newnode;
  }
}

loglist_t * sortList(loglist_t ** inlist) {

	loglist_t * sorted = NULL;

	loglist_t * current = *inlist;

	while (current != NULL) {

		loglist_t *next = current->next;

		sortedInsert(&sorted, current);

		current = current->next;

	}

	return sorted;

}END OLD CODE */

loglist_t * sortList(loglist_t * inlist) {

	//if 1 item or empty, return list
	if (inlist == NULL || inlist->next == NULL)
		return inlist;

	loglist_t *current, *smallest, *smallestPrev, *prev;

	current = inlist;
	smallest = inlist;
	prev = inlist;
	smallestPrev = inlist;

	//finds smallest node
	while (current != NULL) {
		if (strcmp(current->line.timestamp, smallest->line.timestamp) <= 0) {
			smallestPrev = prev;
			smallest = current;
		}

		prev = current;
		current = current->next;
	}

	//switches the first node with the smallest node
	loglist_t * tmp;
	if (smallest != inlist) {
		smallestPrev->next = inlist;
		tmp = inlist->next;
		inlist->next = smallest->next;
		smallest->next = tmp;
	}

	//returns the next one, and continues down until the last bit of the list
	smallest->next = sortList(smallest->next);

	return smallest;

}
