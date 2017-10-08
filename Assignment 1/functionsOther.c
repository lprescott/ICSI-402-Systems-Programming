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

loglist_t * addFirst(loglist_t * list, logline_t templogline){
    /* Declare newNode  here */
    loglist_t * newNode = (loglist_t*)malloc(sizeof(loglist_t));
    if (newNode == NULL){
      fprintf(stderr, "Failed to allocated memory for head of newNode.\n");
      exit(-1);
    }
    newNode->line = templogline;
    newNode->next = list;
    return newNode;
}
