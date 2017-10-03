//Project: Prog1
//Names:   Luke Prescott, Rob Rose, Tommy Li
//Roles:   Leader, Monitor, Recorder Respectively
//Date:    10/3/2017
//Course:  ICSI 402
//Desc:    This file contains the parseLine, deleteList, and printLine functions to be used in main.c

logline* parseLine(string line) {
   char str[] = strdup(line);
   
   char *levelP = strtok(str, ",");
   char *timestampP = strtok(NULL, ",");
   char *messageP = strtok(NULL, " ");
   
   logline parsed = { .level = levelP, .timestamp = timestampP, .message = messageP }
   
   return parsed;
}

void deleteList(loglist* l) {
   
   loglist * head = l;
   loglist * next;
   
   while (current != NULL) {
      next = current->next;
      free(current);
      current = next;
   }
   
   l = NULL;
}

void printLines(logList* l) {  
   
   logList * next;
   char tempLevel[];
   char tempTimestamp[];
   char tempMessage[];
   
   tempLevel = l->level;
   tempTimestamp = l->timestamp;
   tempMessage = l->message;
   
   printf("%s,%s,%s", tempLevel, tempMessage, tempTimestamp);
 
   nextL = l->next;
   
   while (next != NULL) {
      tempLevel = nextL->level;
      tempTimestamp = nextL->timestamp;
      tempMessage = nextL->message;
   
      printf("%s,%s,%s", tempLevel, tempMessage, tempTimestamp);\
      
      next = nextL->next;
   }
   
}
