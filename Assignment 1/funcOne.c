//Desc:    This file contains the parseLine, deleteList, and printLine functions to be used in main.c
#include "structs.h"
#include "headersOnes.h"


/* External variables */
extern struct loglist * inlist;

/*
    Function logline* parseLine(string line) to construct a logline with 3 fields
    based on the input string. Note that this function allocates memory.

    Must check if inputted char line [] has atleast two commas, and print to
    stderr if not.
    
    Must check if log entry looks like <level>,<timestamp>,<message>,
    and print to stderr if not.
*/
//Parses a log file line into a logline struct
struct logline_t * parseLine(char line []) {
   //duplicates the argument line into str
   char str[1000];
   strcpy(str, line);// copies the string into a line.

   //tokenizes str and splits the string by ","
   char * levelP = strtok(str, ",");
   char * timestampP = strtok(NULL, ",");
   char * messageP = strtok(NULL, ",");

   //stores all temp values into a logline struct
   struct logline_t * parsed = (struct logline *) malloc(sizeof(logline_t));

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
void deleteList(loglist_t* head) {

loglist* current = head// head is equal to a pointer of the current node
loglist* next;// next is equal to a pointer of the current node


while(current != NULL)
{
 next= current -> next;
 free(current->line);
 free(current);// deallocates memory from the current node
 current= next;// takes the current node and makes it equal to the next nude


}
   
   head=NULL;

}

//prints all loglines in a loglist
void printLines(struct loglist_t* head) {

    if (head == NULL){
      printf("Empty List");
      return;
    }

   //initalizes all the temp variables
   struct logList_t * next;
   char levelTemp[100];
   char timestampTemp[100];
   char messageTemp[100];

   //sets all things to their temp things
   strcpy(tempLevel, head->line.level);
   strcpy(tempTimestamp, head->line.timestamp);
   strcpy(tempMessage, head->line.message);

   //prints the data elements of the head, which include the level, message, and the timestamp
   printf("%s,%s,%s", levelTemp, messageTemp, timestampTemp);

   // repeats the same process, but for the rest of the linked list.
   while (head->next != NULL) {
      strcpy(levelTemp, l->next->line.level);
      strcpy(timestampTemp, l->next->line.timestamp);
      strcpy(messageTemp, l->next->line.message);

      printf("%s,%s,%s", levelTemp, messageTemp, timestampTemp);\

      head->next = head->next->next;// traversing the linked list.
   
}

