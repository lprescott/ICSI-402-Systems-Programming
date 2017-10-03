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
#include "protoOne.h"
#include "protoTwo.h"

struct logline{
  char level[20];
  char timestamp[20];
  char message[100];
} logline_t;

typedef struct loglist {
  logline_t line;
  struct loglist *next;
} loglist_t;

int main( int argc, char *argv[] )  {

  DIR * dp;
  struct dirent *d;

  FILE * inputFile;
  FILE * outputFile;

  int length = 1024;
  char tempLine[length];

  if( argc == 2 ) {
    /* Operate in the specified directory */
    printf("This program will operate in the following directory: %s\n",       argv[1]);

    if((dp = opendir(argv[1])) == NULL){
     fprintf(stderr, "Cannot open current working directory.\n");
     exit(1);

     while((d = readdir(dp)) != NULL){
      /* Open the current file. */
      //d->d_name is the name of the file
      inputFile = fopen(d->d_name, "r");

      if(inputFile != NULL){
        //do stuff
        fgets(&tempLine, length, inputFile);
        //parseLine(tem0pLine);
        fclose(inputFile);
        }
      closedir(dp);
      }
    }

  else if( argc > 2 ) {
    fprintf(stderr, "Too many arguments supplied.\n");
  }

  else {
    /* Operate in the current working directory. */
   printf("This program will operate in the current working directory.");

   if((dp = opendir(".")) == NULL){
    fprintf(stderr, "Cannot open current working directory.\n");
    exit(1);
   }

   while((d = readdir(dp)) != NULL){
    /* Open the current file. */
    //d->d_name is the name of the file
    inputFile = fopen(d->d_name, "r");

    if(inputFile != NULL){
      //do stuff
      fgets(&tempLine, length, inputFile);
      //parseLine(tempLine);
      fclose(inputFile);
    }
   }
   closedir(dp);
  }

}
