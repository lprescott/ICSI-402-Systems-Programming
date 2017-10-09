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

    loglist_t * temp;
    newNode->line = templogline;

    /* Find tail of list */
    temp = list;
    while(temp->next != NULL){
      temp = temp->next;
    }
    temp->next = newNode;
    newNode->next = NULL;
}
