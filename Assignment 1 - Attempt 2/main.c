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
	FILE * inputFile;
	char tempLine [128];
	char directory [128];
	struct stat buffer;

	/* Declare resultlist */

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

	/* Check permissions of directory */
	stat(directory, &buffer);
	mode_t bits = buffer.st_mode;
	if((bits & S_IRUSR) == 0){
    	//User doesn't have read 
		fprintf(stderr, "Error reading directory.\n");
		exit(-1);
	}

	/* Read through names of files in opened directory */
	while((d=readdir(dp)) != NULL){
		/* The file names are d->d_name */
		if(strcmp(getExtension(d->d_name), ".log") == 0){
			/* Open the file for reading */
			if((inputFile = fopen(d->d_name, "r")) != NULL){
			
			/* Declare inlist here */

			/* Read line by line */
			while(fgets(tempLine, sizeof tempLine, inputFile)!= NULL){
				/* tempLine contains the current line's text */
				/* Add parsed lines to inlist */
					
			}

            /* Sort inlistHere */
			//sortList(inlist);

			/* Call mergeLists */
			//loglist* mergeLists(loglist* resultlist, loglist* inlist);

			/* Call deleteList on inlist */
			//deleteList(loglist* inlist);

			}

			else{
				fprintf(stderr, "Error opening file.\n");
			}

			fclose(inputFile);
		}

	fclose(inputFile);
	
	/* Call printLines  */
	//printLines(loglist_t * resultList){

	}

	/* Close directory */
	if(closedir(dp) != 0){
		fprintf(stderr, "Error closing directory.\n");
	}

	return 1;
}