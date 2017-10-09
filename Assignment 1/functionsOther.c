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

loglist_t * addLast(loglist_t * list, logline_t templogline){
    /* Declare newNode  here */
    loglist_t * newNode = (loglist_t*)malloc(sizeof(loglist_t));

    if (newNode == NULL){
      fprintf(stderr, "Failed to allocated memory newNode.\n");
      exit(-1);
    }

    newNode->line = templogline;
    newNode->next = NULL;

    //check for first insertion
    if(list == NULL){
      list = newNode;
      return list;
    }
    else{
      //initalizes all the temp variables
      loglist_t * temp = list;

      while (temp -> next != NULL){
        temp = temp->next;
      }

      temp->next = newNode;
      return list;
    }
}

void swap(loglist_t * first, loglist_t * second){
  logline_t * temp = malloc(sizeof(logline_t));
  if (temp == NULL){
    fprintf(stderr, "Unable to allocate memory for new temp line.\n");
    exit(-1);
  }

  * temp = first->line;

  strcpy(first->line.level , second->line.level);
  strcpy(first->line.timestamp , second->line.timestamp);
  strcpy(first->line.message , second->line.message);

  strcpy(second->line.level , temp->level);
  strcpy(second->line.timestamp , temp->timestamp);
  strcpy(second->line.message , temp->message);

}
