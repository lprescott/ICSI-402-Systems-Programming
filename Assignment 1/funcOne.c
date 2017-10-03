//Project: Prog1
//Names:   Luke Prescott, Rob Rose, Tommy Li
//Roles:   Leader, Monitor, Recorder Respectively
//Date:    10/3/2017
//Course:  ICSI 402
//Desc:    This file contains the parseLine, deleteList, and printLine functions to be used in main.c

logline* parseLine(string line);
void deleteList(loglist* l);

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
   
   while (next != null) {
      tempLevel = nextL->level;
      tempTimestamp = nextL->timestamp;
      tempMessage = nextL->message;
   
      printf("%s,%s,%s", tempLevel, tempMessage, tempTimestamp);\
      
      next = nextL->next;
   }
   
}
