//Desc:    This file contains the parseLine, deleteList, and printLine functions to be used in main.c
#include "headersOne.h" 
#include "structs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* External variables */
//extern struct loglist_t * inlist;

/*
    Function logline* parseLine(string line) to construct a logline with 3 fields
    based on the input string. Note that this function allocates memory.
    Must check if inputted char line [] has at least two commas, and print to
    stderr if not.
    
    Must check if log entry looks like <level>,<timestamp>,<message>,
    and print to stderr if not.
*/
//Parses a log file line into a logline struct
logline_t * parseLine(char line []) {
   //duplicates the argument line into str
   char str[1000];
   strcpy(str, line);// copies the string into a line.

   //tokenizes str and splits the string by ","
   char * levelP = strtok(str, ",");
   char * timestampP = strtok(NULL, ",");
   char * messageP = strtok(NULL, ",");

   //stores all temp values into a logline struct
  logline_t * parsed = (logline_t *) malloc(sizeof(logline_t));

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

//frees up all memory for the list
void deleteList(loglist_t * head) {

 loglist_t * current = head;// head is equal to a pointer of the current node
 loglist_t * next;// next is equal to a pointer of the current node
 logline_t *currentline;

while(current != NULL)
{
    next= current -> next;
    currentline = &current-> line;
  
    free(current);// deallocates memory from the current node
    free(&currentline);
    current= next;// takes the current node and makes it equal to the next nude
}
   head=NULL;

}

//prints all loglines in a loglist
void printLines( loglist_t * head){

    if (head == NULL){
      printf("Empty List\n");
      return;
    }

   //initalizes all the temp variables
   loglist_t * next;
   char levelTemp[100];
   char timestampTemp[100];
   char messageTemp[100];

   //sets all things to their temp things
   strcpy(levelTemp, head->line.level);
   strcpy(timestampTemp, head->line.timestamp);
   strcpy(messageTemp, head->line.message);

   //prints the data elements of the head, which include the level, message, and the timestamp
   printf("%s,%s,%s", levelTemp, messageTemp, timestampTemp);

   // repeats the same process, but for the rest of the linked list.
   while (head->next != NULL) {
      strcpy(levelTemp, head->next->line.level);
      strcpy(timestampTemp, head->next->line.timestamp);
      strcpy(messageTemp, head->next->line.message);

      printf("%s,%s,%s", levelTemp, messageTemp, timestampTemp);

      head->next = head->next->next;// traversing the linked list.
   
}
}


