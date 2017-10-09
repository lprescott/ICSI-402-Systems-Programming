#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "structs.h"
#include "headersOne.h"
#include "headersTwo.h"
#include "headersOther.h"

/*
To do:
The out of the program should be combinedlogs.log
addFirst must re redone to add on the end of the list
garbage values are being printed in printLines
merge will have to be implemented
sort will have to be tested
Comments must be completed
Testing with other files no supplied
*/
int main( int argc, char *argv[] ) {

	/* Local variables */
	DIR * dp;
	struct dirent * d;
	FILE * inputFile;
	char tempLine [128];
	//struct stat buffer;

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
  }
  else if( argc > 2 ) {
    perror("Error");
  }
  else {
		if((dp = opendir(".")) == NULL){
			perror("Error");
			exit(-1);
		}
		printf("\nThe directory to open is: \".\"\n");
  }

	/* Read through names of files in opened directory */
	while((d=readdir(dp)) != NULL){

		loglist_t * inlist = malloc(sizeof(loglist_t));
		if (inlist == NULL){
			fprintf(stderr, "Failed to allocated memory for head of inlist.\n");
			exit(-1);
		}

		loglist_t * mergeList = malloc(sizeof(loglist_t));
		if (mergeList == NULL){
			fprintf(stderr, "Failed to allocated memory for head of inlist.\n");
			exit(-1);
		}

		/* The file names are d->d_name */
		if(strstr(d->d_name, ".log")){
			printf("\nFile to be read: \"%s\"\n", d->d_name);
			puts("Lines to be parsed:");
			errno =  0;
			/* Open the file for reading */
			if((inputFile = fopen(d->d_name, "r")) != NULL){


				/* Check if file starts with #
				char buf[4];
				fseek(inputFile, 0, SEEK_SET);
				fread(buf, sizeof(buf), 1, inputFile);
				printf("\tThe first char of the file: %c\n", buf[0]);
				rewind(inputFile);
				*/
				/* Check if file begins with hashtag
				if(buf[0] != '#'){
					fprintf(stderr, "File does not begin with a hashtag.\n");
					continue;
				}
				*/
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

						/* Declare templogline struct here */
						logline_t * templogline = malloc(sizeof(logline_t));
						if (templogline == NULL){
							fprintf(stderr, "Failed to allocated memory for head of templogline.\n");
							exit(-1);
						}

						/* Parse tempLine into templogline struct here */
						templogline = parseLine(tempLine);

						/* Print for piece of mind */
						fputs(tempLine, stdout);

						/* Add templogline to on end of inlist*/
						addLast(inlist, * templogline);

					}
				}
				/* inlist is ready */
				//sort
				inlist = sortList(inlist);

				/* Print lines of inlist again for peace of mind */
				puts("\n");
				printLines(inlist);

				/* Print for peace of mind */
				//fprintf(stdout, "\n\nThe third line message in inlist: %s", inlist->next->next->line.message);

				// merge here


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


	/* Print for piece of mind */
	fputs("\nDone.", stdout);
	//perror("ERROR");
	fclose(inputFile);
 	return 1;

}
