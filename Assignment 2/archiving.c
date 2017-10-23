//Project: 	Prog1
//Names:   	Luke Prescott, Rob Rose, Tommy Li (lprescott@albany.edu, rwrose@albany.edu, tli3@albany.edu)
//Roles:   	Leader, Monitor, Recorder Respectively
//Date:    	10/19/2017
//Course:  	ICSI 402
//Desc: contains the two functions, archive which creates an archive file from a set of individual files
//         unarchive function unpacks an archive file and create

//Input:
//Output:
//Assumption:



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "archiving.h"
#include "constants.h"
#include "other.h"
#include "archivingSize.h"

/* Constants to use:
define sizeNumFiles 4 //1
define sizeFileSize 4 //2
define sizeLengthFile 1 //3
define sizeFileName 256 //4
*/

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

void archive(char** fileNames, int numFiles, char* archiveName) {
	//Variables here
	char * tempArchiveName; //the temporary character array containing the archive name
	tempArchiveName = strdup(archiveName); //duplicate data to above array
	FILE * outputFile; //The output file
	FILE * tempFile; //The temp file (input file)
	int tempNumOfFiles = numFiles; //Assigning a temporary int the number of files

	// concatenate ".bin" to a temp archiveName string.
	if (strstr(tempArchiveName, ".bin") == NULL){
		strcat(tempArchiveName, ".bin");
	}

	//opens a new bin file with new string for writing
	if ((outputFile = fopen(tempArchiveName, "wb")) == NULL){
		fprintf(stderr, "Could not allocate space for the output archive.");
		exit(-1);
	}
	
	//Add number of files to bin
	//printf("NUMBER OF FILES: %d\n", tempNumOfFiles);
	fwrite(&tempNumOfFiles, sizeNumFiles, 1, outputFile);
	
	//loop for the number of files
	int i = 0;
	for (i = 0; i < numFiles; i++) {
		
		char * tempFileName; //a character array for the inputfile's name
		tempFileName = strdup(fileNames[i]); //assign the inputfile's name
		
		//printf("File Name: %s\n", tempFileName);
		
		//Attempt to dynamically allocate space
		if ((tempFile = fopen(tempFileName, "r")) == NULL) {
			fprintf(stderr, "could not allocate space");
			exit(-1);
		}
		
		long lengthOfFileName = strlen(tempFileName) + 1; //A new long variable containing the length of the file name + 1
		
		//Add length of file name to bin
		//printf("%d\n", lengthOfFileName);
		fwrite(&lengthOfFileName, sizeof(int), 1, outputFile);
		
		//Add filename to bin
		fwrite(tempFileName, sizeof(char), lengthOfFileName, outputFile);
		
		//Create and assign a long variable that contains the fileSize of the current file
		long tempSize = (fileSize(tempFile));
		//printf("%d\n", tempSize);
		
		//Add the fileSize to the bin
		fwrite(&tempSize, sizeof(long), 1, outputFile);
			
		int c; //A int variable containing characters to add
		int count = 0; //A count variable to keep track in the loop
		
		//Add character by character to the bin file (while not meeting the end of inputFile)
		while((c = fgetc(tempFile)) != EOF) {
			count++;
			char h = (char)c;
			//printf("%c", h);
			fprintf(outputFile, "%c", h);
		}
		
		//printf("%d", count);
		
	}

	fclose(outputFile);
	
}//End archive



void unarchive(char* archiveFile) {

	
	//Variables here
	char * tempArchiveName;
	int numOfFiles, fileNameLength;
	long contentSize;
	tempArchiveName = strdup(archiveFile);
	FILE * inputFile;
	FILE * tempFile;

	// concatenate ".bin" to a temp archiveName string.
	if (strstr(tempArchiveName, ".bin") == NULL){
		strcat(tempArchiveName, ".bin");
	}

	//opens a new bin file with new string for reading
	if ((inputFile = fopen(tempArchiveName, "rb")) == NULL){
		fprintf(stderr, "Could not allocate space for the input archive.");
		exit(-1);
	}

	fread(&numOfFiles, sizeNumFiles, 1, inputFile);

	printf("\nNumber of Files: %d\n", numOfFiles);
	
	int i = 0;
	for (i = 0; i < numOfFiles; i++) {
		fread(&fileNameLength, sizeof(int), 1, inputFile);
		printf("%d\n", fileNameLength);
		
		char * tempString = malloc(fileNameLength * sizeof(char));
		
		if (tempString == NULL) {
			exit(-1);
		}
		
		fread(tempString, sizeof(char), fileNameLength, inputFile);
		
		printf("File Name: %s\n", tempString);
		
		tempFile = fopen(tempString, "w");
		if (tempFile == NULL) {
			exit(-1);
		}
		
		fread(&contentSize, sizeof(long), 1, inputFile);
		printf("%d\n", contentSize);
		
		int y = 0;
		int c;
		for (y; y < contentSize; y++) {
			fread(&c, sizeof(char), 1, inputFile);
			fwrite(&c, sizeof(char), 1, tempFile);
		}
		
	}
	
}

