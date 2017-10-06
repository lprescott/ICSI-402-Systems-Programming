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
   char * messageP = strtok(NULL, " ");

   //stores all temp values into a logline struck
   struct logline * parsed = (struct logline *) malloc(sizeof(logline_t));
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
void printLines(loglist* l) {

   //initalizes all the temp variables
   logList * next;
   char tempLevel[];
   char tempTimestamp[];
   char tempMessage[];

   //sets all things to their temp things
   tempLevel = l->level;
   tempTimestamp = l->timestamp;
   tempMessage = l->message;

   //print the head data
   printf("%s,%s,%s", tempLevel, tempMessage, tempTimestamp);

   nextL = l->next;

   //repeat but for the rest of the list
   while (next != NULL) {
      tempLevel = nextL->level;
      tempTimestamp = nextL->timestamp;
      tempMessage = nextL->message;

      printf("%s,%s,%s", tempLevel, tempMessage, tempTimestamp);\

      next = nextL->next;
   }

}
*/

/*Reference push.

void push(node_t * head, int val) {
    node_t * current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = malloc(sizeof(node_t));
    current->next->val = val;
    current->next->next = NULL;
}

//NOT WORKING ATM

//Inserts a logLine into a logList.

*/

void insert(loglist_t * head, logline_t headLine) {
  loglist_t * current = head;
  while (current->next != NULL) {
      current = current->next;
  }

  current->next = malloc(sizeof(loglist_t));
  current->next->line = headLine;
  current->next->next = NULL;
}

/*

void insert(loglist_t * head, logline_t headLine) {

   struct loglist toInsert = {.line = headLine, next = NULL};

   if (head == NULL) {
      head = toInsert;
      return;
   }

   struct loglist * current = head;
   while (current->next != NULL) {
      current = current->next;
   }
   current->next = toInsert;

}
*/
