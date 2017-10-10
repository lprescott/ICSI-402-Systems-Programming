//Project: 	Prog1
//Names:   	Luke Prescott, Rob Rose, Tommy Li (lprescott@albany.edu, rwrose@albany.edu, tli3@albany.edu)
//Roles:   	Leader, Monitor, Recorder Respectively
//Date:    	10/3/2017
//Course:  	ICSI 402
//Desc:    	This program takes directory full of log files then concatonates them into
//         	a single log file, where the order is based on the time of each log.
//Input:   	The program can take a command line argument specifying the path where the program will execute
//	   	Otherwise, it will execute in the current directory
//Output:  	A .log file and standard output of the printed merge list
//Assumption:	The possible command line argument is assumed to be a unix path to a directory in unix.

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>

#include "structs.h"
#include "headersOne.h"
#include "headersTwo.h"
#include "headersOther.h"

/*
To do:
*Comments must be completed, one person will each function
*Testing with other files nor supplied
*refactor any code
*error checking: if file includes #, format of a log file level, date, timestamp, message
*double check and reread assignment requirements.
*/

int main( int argc, char *argv[] ) {

	/* Local variables */
	DIR * dp;
	struct dirent * d;
	FILE * inputFile;
  	FILE * outputFile;
	char tempLine [128];
	char * outputName = "combinedlogs.log"; 
	char currentDirectory[128];
	char outputPath[128];


	/* Declare resultlist head here */
	loglist_t * resultlist = malloc(sizeof(loglist_t));
	if (resultlist == NULL){
		fprintf(stderr, "Failed to allocated memory for head of resultlist.\n");
		exit(-1);
	}

	/* Determine directory */
  	if( argc == 2 ) {
    	if((dp = opendir(argv[1])) == NULL){
      		perror("Error");
      		exit(-1);
    	}
		printf("The directory opened is: \"%s\"\n", argv[1]);
		strcpy(currentDirectory, argv[1]);
		strcat(currentDirectory, "/");
	}
	  
  	else if( argc > 2 ) {
    	fprintf(stderr, "Too many arguments!.\n");
		exit(-1);
  	}
  
	else {
		if((dp = opendir(".")) == NULL){
			perror("Error");
			exit(-1);
		}
		printf("\nThe directory to open is: \".\"\n");
		strcpy(currentDirectory, "./");
    
  	}

	strcpy(outputPath, currentDirectory);
	strcat(outputPath, outputName);
	outputFile = fopen(outputPath, "w");
	  
	/* Read through names of files in opened directory */
	while((d=readdir(dp)) != NULL){

		loglist_t * inlist = NULL;
		inlist = malloc(sizeof(loglist_t));
		if (inlist == NULL) {
				fprintf(stderr, "Failed to allocated memory for head of inlist.\n");
				exit(-1);
		}
		/* The file names are d->d_name */
		if(strstr(d->d_name, ".log")){
			char filePath[128];
			filePath[0] = '\0';
			strcpy(filePath, currentDirectory);
			strcat(filePath, d->d_name);

			printf("\nFile to be read: \"%s\"\n", d->d_name);
			puts("Lines to be parsed:");
			errno =  0;
			/* Open the file for reading */
			if((inputFile = fopen(filePath, "r")) != NULL){

				loglist_t * inlist = NULL;
				inlist = malloc(sizeof(loglist_t));
				if (inlist == NULL) {
						fprintf(stderr, "Failed to allocated memory for head of inlist.\n");
						exit(-1);
				}
				inlist->next = NULL;

				/* Check if file starts with # */

				/* Read line by line */
				while(fgets(tempLine, sizeof tempLine, inputFile)!= NULL){

					/* Look at lines only without hashtags */
					if (strstr(tempLine, "#") != NULL){
						continue;
					}
					// Check if tempLine contains at least two commas
					else if ((containsTwoPlusCommas(tempLine)) == 0){
						fprintf(stderr, "Log entry does not contains at least two commas.\n");
						exit(-1);
					}
					/*
					// Check if tempLine looks like <level>,<timestamp,<message>
					else if ((looksCorrect(tempLine)) == 0){
						fprintf(stderr, "Log entry does not looks like <level>,<timestamp,<message>.\n");
						exit(-1);
					}
					*/
					else{

						/* Parse tempLine into templogline struct here */
						logline_t * templogline = parseLine(tempLine);

						/* Print for piece of mind */
						fputs(tempLine, stdout);

						/* Add templogline to on end of inlist*/
						inlist = addLast(inlist, * templogline);

					}
				}
				/* inlist is ready */
				//sort
				//inlist = sortList(inlist);

				/* Print lines of inlist again for peace of mind */
				puts("\n");
				printLines(inlist);

				/* Print for peace of mind */
				//fprintf(stdout, "\n\nThe third line message in inlist: %s", inlist->next->next->line.message);

				// merge here
				//puts("Merge attempted.");
				resultlist = mergeLists(resultlist, inlist);
				printf("\nMERGEDLISTS\n\n");
				
				printLines(resultlist);

				printf("\n\nMERGED SORTED LIST\n\n");
				sortList(resultlist);
				printLines(resultlist);
        

				/* inlist is deleted */
				deleteList(inlist);
			}
			else if (inputFile == NULL){
				perror("Error");
				exit(-1);
			}
		}
	}


	/* Close directory */
	if(closedir(dp) != 0){
		fprintf(stderr, "Error closing directory.\n");
	}
 
 printToFile( resultlist, outputFile);


	/* Print for piece of mind */
	fputs("\nDone.", stdout);
	//perror("ERROR");
	fclose(inputFile);
 	return 1;

}
