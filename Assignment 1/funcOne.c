//Project: Prog1
//Names:   Luke Prescott, Rob Rose, Tommy Li
//Roles:   Leader, Monitor, Recorder Respectively
//Date:    10/3/2017
//Course:  ICSI 402
//Desc:    This file contains the parseLine, deleteList, and printLine functions to be used in main.c

#include <stdlib.h>
#include <stdio.h>
#include "protoOne.h"
#include "structs.h"

/* External variables */
extern struct loglist * inlist;
//extern struct logline * inlineHead;
//extern logline_t * headLine;

/*

typedef struct logline{
  char level[20];
  char timestamp[20];
  char message[100];
} logline_t;


*/

//Parses a log file line into a logline struct
struct logline * parseLine(char line []) {
   //duplicates the argument line into str
   char str[1024];
   strcpy(str, line);

   //tokenizes str and splits the string by ","
   char * levelP = strtok(str, ",");
   char * timestampP = strtok(NULL, ",");
   char * messageP = strtok(NULL, ",");

   //stores all temp values into a logline struck
   struct logline * parsed = (struct logline *) malloc(sizeof(logline_t));

   if(parsed == NULL){
    fprintf(stderr, "Unable to allocate memory for new line\n");
    exit(-1);
    }

   strcpy(parsed->level , levelP);
   strcpy(parsed->timestamp , timestampP);
   strcpy(parsed->message , messageP);

   //returns logline
   return parsed;
}

/*


//frees up all memory for the list
void deleteList(loglist* l) {

   //initializes necessary variables
   loglist * head = l;
   loglist * next;


   //loops through list and frees up all memory
   while (current != NULL) {
      next = current->next;
      free(current->line);
      free(current);
      current = next;
   }

   //sets the initial list to null, freeing all the memory
   l = NULL;
}


//prints all loglines in a loglist
void printLines(struct loglist* l) {

    if (l == NULL){
      puts("The list is empty");
      return;
    }

   //initalizes all the temp variables
   struct logList * next;
   char tempLevel[64];
   char tempTimestamp[64];
   char tempMessage[64];

   //sets all things to their temp things
   strcpy(tempLevel, l->line.level);
   strcpy(tempTimestamp, l->line.timestamp);
   strcpy(tempMessage, l->line.message);

   //print the head data
   printf("%s,%s,%s", tempLevel, tempMessage, tempTimestamp);

   //repeat but for the rest of the list
   while (l->next != NULL) {
      strcpy(tempLevel, l->next->line.level);
      strcpy(tempTimestamp, l->next->line.timestamp);
      strcpy(tempMessage, l->next->line.message);

      printf("%s,%s,%s", tempLevel, tempMessage, tempTimestamp);\

      l->next = l->next->next;
   }
}
*/
