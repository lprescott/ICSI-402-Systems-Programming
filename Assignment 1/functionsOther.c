#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "structs.h"
#include "headersOther.h"

/*
int looksCorrect(char * line){
    if(){
        return 1;
    }
    else{
      else return 0;
    }
}
*/

int containsTwoPlusCommas(char * line){
    int count = 0;
    int x = 0;
    while(line[x] != EOF){
      if (line[x] == ','){
        count ++;
      }
      x++;
    }

    if (count >= 2){
      return 1;
    }

    else return 0;
}

void addLast(loglist_t * list, logline_t templogline){
    /* Declare newNode  here */
    loglist_t * newNode = (loglist_t*)malloc(sizeof(loglist_t));

    if (newNode == NULL){
      fprintf(stderr, "Failed to allocated memory newNode.\n");
      exit(-1);
    }

    newNode->line = templogline;
    newNode->next = NULL;

    //initalizes all the temp variables
  	loglist_t * temp;
  	temp = list;

    //check for first insertion
    if(temp->next == NULL){
      temp->next = newNode;
      printf("... was added at beginning\n");
    }
    else{
        //else loop through the list and find the last
        //node, insert next to it
        loglist_t * current = temp;
        while (1) { // Change 2
            if(current->next == NULL)
            {
                current->next = newNode;
                printf(" ...was added later\n");
                break; // Change 3
            }
            current = current->next;
        };
    }
}

void moveNode(loglist_t ** dest, loglist_t ** source) {

	loglist_t *newnode = *source;

	*source = newnode->next;

	newnode->next = *dest;

	*dest = newnode;

}
