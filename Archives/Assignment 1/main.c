//Project: Prog1
//Names:   Luke Prescott, Rob Rose, Tommy Li
//Roles:   Leader, Monitor, Recorder Respectively
//Date:    10/3/2017
//Course:  ICSI 402
//Desc:    This program takes directory full of log files then concatonates them into
//         a single log file, where the order is based on the time of each log.

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

#include "structs.h"

#include "protoOne.h"
//#include "protoTwo.h"

#include "funcOne.c"
//#include "funcTwo.c"

/* Global variables here. */

/* Protypes here. */
void scanDirectory ( char directory [] );
void addOnEnd (loglist_t * head, logline_t line);

/* Begin main method here. */
int main( int argc, char *argv[] )  {

  if( argc == 2 ) {
    /* Operate in the specified directory */
    printf("This program will operate in the following directory: %s\n", argv[1]);

    //Scans every file line by line inputtng parsedlines into inlist (unsorted atm)
    scanDirectory(argv[1]);
    puts("Done.");
  }

  else if( argc > 2 ) {
    fprintf(stderr, "Too many arguments supplied.\n");
  }

  else {
    /* Operate in the current working directory. */
    printf("This program will operate in the current working directory.");

    //Scans every file line by line inputtng parsedlines into inlist (unsorted atm)
    scanDirectory(".");
    puts("Done.");
 }
} /*End main*/

/* Begin scanDirectory */
void scanDirectory ( char directory [] ){

  DIR * dp;
  struct dirent *d;

  FILE * inputFile;
  FILE * outputFile;

  int length = 1024;
  char tempLine[length];

  /* Dynamically allcoated memory for loglist inlist */
  struct loglist * inlist = NULL;
  inlist = malloc(sizeof(struct loglist));

  if(inlist == NULL){
    fprintf(stderr, "Unable to allocate memory for new node\n");
    exit(-1);
  }

  if((dp = opendir(directory)) == NULL){
    fprintf(stderr, "Cannot open current working directory.\n");
    exit(-1);
  }

 while((d = readdir(dp)) != NULL){
   /* Open the current file. */
   //d->d_name is the name of the file

   inputFile = fopen(d->d_name, "r");
   //puts(d->d_name);

   if(inputFile != NULL){
     //do stuff
     while(fgets(tempLine, sizeof tempLine, inputFile)!= NULL) {
       if (tempLine[0] == '#') continue;
        printf(tempLine);
        struct logline * tempParsedLine =  parseLine(tempLine);

        printf("\nRead level: %s\n", tempParsedLine->level);
        printf("\nRead timestamp: %s\n",tempParsedLine->timestamp);
        printf("\nRead message: %s\n",tempParsedLine->message);

        /* Insert tempParsedLine into inlist here. */
        addOnEnd(inlist, * tempParsedLine);
     }
     fclose(inputFile);
   }
   //printLines(inlist);
 }
 closedir(dp);
}

/* Begin addOnEnd --
https://stackoverflow.com/questions/5797548/c-linked-list-inserting-node-at-the-end

note: memory must be allocated for each new loglist AND linelist for functionality
*/
void addOnEnd (loglist_t * head, logline_t line){
  //create new node
     loglist_t * newNode = (loglist_t*)malloc(sizeof(loglist_t));
     logline_t * newLine = (logline_t*)malloc(sizeof(logline_t));

     if(newNode == NULL){
         fprintf(stderr, "Unable to allocate memory for new node\n");
         exit(-1);
     }

     if(newLine == NULL){
         fprintf(stderr, "Unable to allocate memory for new line\n");
         exit(-1);
     }

     strcpy(newLine->level , line.level);
     strcpy(newLine->timestamp , line.timestamp);
     strcpy(newLine->message , line.message);

     newNode->line = * newLine;
     newNode->next = NULL;

     //check for first insertion
     if(head->next == NULL){
         head->next = newNode;
         printf("added at beginning\n");
     }

     else
     {
         //else loop through the list and find the last
         //node, insert next to it
         loglist_t *current = head;
         while (current->next != NULL) {
           current = current->next;
         }
         current->next = newNode;
         printf("added later\n");
     }

} /*End addOnEnd */
