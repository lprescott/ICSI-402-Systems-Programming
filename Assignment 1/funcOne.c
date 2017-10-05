//Project: Prog1
//Names:   Luke Prescott, Rob Rose, Tommy Li
//Roles:   Leader, Monitor, Recorder Respectively
//Date:    10/3/2017
//Course:  ICSI 402
//Desc:    This file contains the parseLine, deleteList, and printLine functions to be used in main.c


//Parses a log file line into a logline struct
logline* parseLine(char[] line) {
   //duplicates the argument line into str
   char str[] = strdup(line);
   
   //tokenizes str and splits the string by ","
   char *levelP = strtok(str, ",");
   char *timestampP = strtok(NULL, ",");
   char *messageP = strtok(NULL, " ");
   
   //stores all temp values into a logline struck
   logline parsed = (logline*) malloc(sizeOf(logline))
   parsed = { .level = levelP, .timestamp = timestampP, .message = messageP }
   
   //returns logline
   return parsed;
}

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
void printLines(logList* l) {  
   
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

//Inserts a logLine into a logList, sorting them as it goes.
void insert(logList * head, logLine ins) {
   
   logList toInsert = {.line = ins, next = NULL};
   
   if (head == NULL) {
      head = toInsert;
      return;
   }
   
   logList * current = head;
   while (current->next != NULL) {
      current = current->next;
   }
   current->next = toInsert;
   
}
