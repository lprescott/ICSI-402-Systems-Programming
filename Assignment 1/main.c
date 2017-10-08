#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "structs.h"
#include "headersOne.h"
#include "headersTwo.h"
#include "headersOther.h"

int main( int argc, char *argv[] )  {

	/* Local variables */
	DIR * dp;
	struct dirent * d;
	FILE * inputFile = NULL;
	char tempLine [128];
	char directory [128];
	struct stat buffer;
	char firstChar = '#';

	/* Determine directory */
	if( argc == 2 ) {
		char * directory = argv[1];
		if((dp = opendir(directory)) == NULL){
			fprintf(stderr, "Error opening directory.\n");
			exit(-1);
		}
	}

	else if( argc > 2 ) {
		fprintf(stderr, "Too many arguments supplied.\n");
	}

	else {
		char * directory = ".";
		if((dp = opendir(directory)) == NULL){
			fprintf(stderr, "Error opening directory.\n");
			exit(-1);
		} 
	}

	/* Read through names of files in opened directory */
	while((d=readdir(dp)) != NULL){
		/* The file names are d->d_name */
		
		/* Print for piece of mind */
		printf("File name: %s\n", d->d_name);	

		/* Open the file for reading */
		if((inputFile = fopen(d->d_name, "r")) != NULL){

			/* Check if file begins with # */

			/* Declare inlist here */
			loglist_t * inlist = NULL;
			if((inlist = malloc(sizeof(loglist_t))) == NULL){
				fprintf(stderr, "Unable to allocate memory for new node\n");
				exit(-1);
			}

			logline_t * tempLineStruct = NULL;
			if((tempLineStruct = malloc(sizeof(logline_t))) == NULL){
				fprintf(stderr, "Unable to allocate memory for new temp line structure.\n");
				exit(-1);
			}

			/* Read line by line */
			while(fgets(tempLine, sizeof tempLine, inputFile)!= NULL){
				/* tempLine contains the current line's text */
				if (strstr(tempLine, "#")){
					continue;
				}

				/* Check if each line contains commas */
				if (containsCommas(tempLine) == 0){
					fprintf(stderr, "1. Unexpected formatting encountered.\n");
					exit(-1);
				}

				/* Check if Log entry doesn't look" like <level>,<timestamp>,<message>. */
				if ((strstr(tempLine, ",") == NULL) || (strstr(tempLine, "-") == NULL) || (strstr(tempLine, ":") == NULL)) {
					fprintf(stderr, "2. Unexpected formatting encountered.\n");
					exit(-1);
				}

				/* Add parsed lines to inlist */
				tempLineStruct = parseLine(tempLine);
				
				/* Print for piece of mind */
				fputs(tempLine, stdout);	
				
				
				/*
				tempLineStruct->level
				tempLineStruct->timestamp
				tempLineStruct->message
				*/

				/* Add to inlist here. */
				//add(inlist, * tempLineStruct);


			}

			/* Free tempLineStruct */
			free(tempLineStruct);

			/* Temporary print inlist here */
			//printLines(inlist);

			/* Sort inlistHere */
			//sortList(inlist);

			/* Call mergeLists */
			//loglist* mergeLists(loglist* resultlist, loglist* inlist);

			/* Call deleteList on inlist */
			//deleteList(loglist* inlist);

			/* Free inlist */
			free(inlist);
			
		}
	
		/* Call printLines  */
		//printLines(loglist_t * resultList){

	}

	/* Close directory */
	if(closedir(dp) != 0){
		fprintf(stderr, "Error closing directory.\n");
	}

	fclose(inputFile);
	return 1;
}