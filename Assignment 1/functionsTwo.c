//Project: 	Prog1
//Names:   	Luke Prescott, Rob Rose, Tommy Li (lprescott@albany.edu, rwrose@albany.edu, tli3@albany.edu)
//Roles:   	Leader, Monitor, Recorder Respectively
//Date:    	10/3/2017
//Course:  	ICSI 402
//Desc:    	This program takes directory full of log files then concatonates them into
//         	a single log file, where the order is based on the time of each log.
//Input:   	The program can take a command line argument specifying the path where the program will execute
//	   	Otherwise, it will execute in the current directory
//Output:  	A .log file and standard output of the printed merge list
//Assumption:	The possible command line argument is assumed to be a unix path to a directory in unix.

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

void swap(loglist_t * a, loglist_t * b) {
	logline_t data = a->line;
	a->line = b->line;
	b->line = data;
}

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

	

	int tru = 0;

	do{
		tru = 0;
		temp = inlist;
		while (temp->next != NULL)
		{
			
			if(strcmp(temp->line.timestamp, temp->next->line.timestamp) > 0)
			{
				swap(temp, temp->next);
				tru = 1;
			}
			temp = temp->next;
		}
	} while (tru == 1);

}
