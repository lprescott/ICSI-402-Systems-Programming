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

typedef struct logline{
  char level[20];
  char timestamp[20];
  char message[100];
} logline_t;

typedef struct loglist {
  logline_t line;
  struct loglist *next;
} loglist_t;

/* Global variables here. */
loglist head = (loglist *)malloc(sizeof(loglist));


void funcName ( char directory [] );

int main( int argc, char *argv[] )  {
  if( argc == 2 ) {
    /* Operate in the specified directory */
    printf("This program will operate in the following directory: %s\n", argv[1]);
    funcName(argv[1]);
    puts("Done.");
  }

  else if( argc > 2 ) {
    fprintf(stderr, "Too many arguments supplied.\n");
  }

  else {
    /* Operate in the current working directory. */
    printf("This program will operate in the current working directory.");
    funcName(".");
 }
}

void funcName ( char directory [] ){
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
   puts(d->d_name);

   if(inputFile != NULL){
     //do stuff
     while(fgets(tempLine, sizeof tempLine, inputFile)!= NULL) {
       fprintf(stdout, "%s", tempLine);
       insert(head, parseLine(tempLine));
     }
     fclose(inputFile);
   }
 }
 closedir(dp);
}
