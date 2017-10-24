//Project: 	Prog1
//Names:   	Luke Prescott, Rob Rose, Tommy Li (lprescott@albany.edu, rwrose@albany.edu, tli3@albany.edu)
//Roles:   	Leader, Monitor, Recorder Respectively
//Date:    	10/19/2017
//Course:  	ICSI 402
//Desc:    	// this contains additional functions needed for the functionality of the main.c file

//including libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//including headers
#include "other.h"
#include "constants.h"
#include "archiving.h"

/*
  This function checks to see if the given character array string is a flag. if it is, the program
  returns -1, else the function will return 1 and exit. It only takes one parameter, a char array that
  will be compared to known flags for the archiver program.
*/
int checkIfFlag(char * string){
    if(strcmp(string, "-a") == 0){
        //This would be a duplicate of the -a flag
        fprintf(stderr, "Multiple flags detected. ");
        return -1;
    }
    else if(strcmp(string, "-u") == 0){
        //This would be a duplicate of the -u flag
        fprintf(stderr, "Multiple flags detected. ");
        return -1;
    }
    else if(strcmp(string, "-v") == 0){
        //This would be a duplicate of the -v flag
        fprintf(stderr, "Multiple flags detected. ");
        return -1;
    }
    else if(strcmp(string, "-l") == 0){
        //This would be a duplicate of the -l flag
        fprintf(stderr, "Multiple flags detected. ");
        return -1;
    }

    return 1;
}

/*
    This function loops through entire array, and if name is == fileNames the function returns the index, else it returns -1;
    For parameters, this functions takes the string array of file names, the number of files, and the name to use in comparisons.
*/
int checkIfContains(char ** fileNames, int numFiles, char * name) {
	
	//i for loop
	int i;
    
    //This loops through the number of files supplied, comparing the string at the index with name
    //returning the location (index) of the correct file name.
	for (i = 0; i < numFiles; i++) {
		if (strcmp(fileNames[i], name) == 0) {
			//printf("\n index Given : %d", i);
			return i;
		}
	}
    
    //If nothing else it returns -1
	return -1;
}

/*
	isnumber returns the value of string in int form if it is a number, or -1 if it is not.
	This function takes char * string and returns a long number.
*/

long isnumber(char * string) {
	long number = -1;	//Number to be returned, defaulted to -1;
	
	//For loops, checks if each character is a digit using isdigit function, if it isn't returns -1;
	int i = 0;
	for (i = 0; i < strlen(string); i++) {
		if (!isdigit(string[i])) {
			return -number;
		}
	}
	
	//Converts string and puts the value into number
	sscanf(string, "%d", &number);
	
	return number;
}

/*
	The archive function returns nothing. It accepts, however, three variables: a string array containing all file names
	that are included in the archiving process, an integer for the number of files included, and a string that is to be the 
	name of the archive created. The archive functions programatically writes details and contents of supplied files to 
	the supplied archivename in the following format: 
		4 bytes containing the number of file; then for each file: 1 byte for the length of the name; the name in string format;
		the size of the contents (in 4 bytes); the actual contents.
*/

/* loop for numFiles through string array
	a)open file
	b) get, store, print size of fileName
	c) get, store, print the fileName
	d) get, store, print size of contents( use fileSize() function here)
	e) get, store , print the contents
	f) close file
*/

void archiveSize(char** fileNames, int numFiles, char* archiveName, long fileSizeLimit) {
	
	//variables
	char * tempArchiveName = strdup(archiveName); //Name for archive;
	FILE * outputFile, * tempFile; //outputFile and the temp file for input, respectively
	int archiveFileCapper = 0, filesPerArchive = 0; //number to go on the end of the archive file name, then a temp
	//int to detail how many files there are per archive
	long sizePerFile = 0; //the size of each file in bytes
	long sumOfFileSize = 0;
	
	// concatenate ".bin" to a temp archiveName string.
	if (strstr(tempArchiveName, ".bin") == NULL){
		strcat(tempArchiveName, ".bin");
	}

	//opens a new bin file with new string for writing
	if ((outputFile = fopen(tempArchiveName, "wb")) == NULL){
		fprintf(stderr, "Could not allocate space for the output archive.");
		exit(-1);
	}
	
	//for loop (for testing RN)
	int i;
	for (i = 0; i < numFiles; i++) {
		
		printf("\nLOOP %d\n", (i + 1));
		
		char * tempFileName; //a character array for the inputfile's name
		tempFileName = strdup(fileNames[i]); //assign the inputfile's name
		
		//printf("File Name: %s\n", tempFileName);
		
		//Attempt to dynamically allocate space
		if ((tempFile = fopen(tempFileName, "r")) == NULL) {
			fprintf(stderr, "could not allocate space");
			exit(-1);
		}
		
		//Initializes sizePerFile
		sizePerFile = fileSize(tempFile); printf("\nsize for file %d: %d\n", (i+1), sizePerFile);
		
		//Adds sizePerFile to sumOfFileSize
		sumOfFileSize += sizePerFile;
		
		if (sumOfFileSize > fileSizeLimit) {
			printf("\nTHE LIMIT IS OVER RE INITIALIZE outputFile as outputfile + archiveFileCapper\n");
			sumOfFileSize = 0;
			if (sizePerFile > fileSizeLimit) {
				
				//figure out how to mathematically figure out how many files need to be made
				int filesSplitBetween = 1 + ((sizePerFile - 1) / fileSizeLimit);
				printf("\nthe single file size is greater than the fileSizeLimit, split into %d files\n", filesSplitBetween);
				
			}
			//reinitialize
		}
		
		//close and freeing;
		fclose(tempFile);
		free(tempFileName);
		
	}
	
}//End archive
