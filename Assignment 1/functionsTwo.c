#include "structs.h"
#include "headersTwo.h"

/*
	Function loglist* mergeLists(loglist* resultlist, loglist* inlist) to merge
	sorted linked list inlist into resultlist and return a pointer to the head of the
	combined list.
*/
loglist_t * mergeLists(loglist_t * resultlist, loglist_t * inlist){
	
}

/*
	Function loglist* sortList(loglist* inlist) to sort the provided linked list inlist
	and return a pointer to the head of the sorted list.
*/
void sortedInsert(loglist_t ** inlist, loglist_t * newnode) {
  loglist_t * current;

  if (*inlist == NULL || (strcmp (*inlist->line.timestamp , newnode->line.timestamp) >= 0)) {
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

}
