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

void scanDirectory ( char directory [] );

int main( int argc, char *argv[] )  {

  struct loglist_t * head = (struct loglist_t *) malloc(sizeof(loglist_t));
  struct logline_t * headLine = (struct logline_t *) malloc(sizeof(logline_t));

  if( argc == 2 ) {
    /* Operate in the specified directory */
    printf("This program will operate in the following directory: %s\n", argv[1]);
    scanDirectory(argv[1]);
    puts("Done.");
  }

  else if( argc > 2 ) {
    fprintf(stderr, "Too many arguments supplied.\n");
  }

  else {
    /* Operate in the current working directory. */
    printf("This program will operate in the current working directory.");
    scanDirectory(".");
    puts("Done.");
 }
}

void scanDirectory ( char directory [] ){
  DIR * dp;
  struct dirent *d;

  FILE * inputFile;
  FILE * outputFile;

  int length = 1024;
  char tempLine[length];

  if((dp = opendir(directory)) == NULL){
    fprintf(stderr, "Cannot open current working directory.\n");
    exit(1);
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
        //printf(tempParsedLine->level);
        //printf(tempParsedLine->timestamp);
        //printf(tempParsedLine->message);
       //insert(head, parseLine(tempLine));
     }
     fclose(inputFile);
   }
 }
 closedir(dp);
}
