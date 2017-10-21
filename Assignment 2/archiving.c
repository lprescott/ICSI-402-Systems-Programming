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

*/

/* loop for numFiles through string array
	a)open file
	b) get, store, print size of fileName
	c) get, store, print the fileName
	d) get, store, print size of contents( use fileSize() function here)
	e) get, store , print the contents
	f) close file
*/
//close bin file

void archive(char** fileNames, int numFiles, char* archiveName) {
	//Variables here
	char * tempArchiveName;
	tempArchiveName = strdup(archiveName);
	FILE * outputFile;
	FILE * tempFile;
	int tempNumOfFiles = numFiles;

	// concatenate ".bin" to a temp archiveName string.
	if (strstr(tempArchiveName, ".bin") == NULL){
		strcat(tempArchiveName, ".bin");
	}

	//opens a new bin file with new string for writing
	if ((outputFile = fopen(tempArchiveName, "wb")) == NULL){
		fprintf(stderr, "Could not allocate space for the output archive.");
		exit(-1);
	}
	
	printf("%d\n", tempNumOfFiles);
	fwrite(&tempNumOfFiles, sizeNumFiles, 1, outputFile);
	
	int i = 0;
	for (i = 0; i < numFiles; i++) {
		
		char * tempFileName;
		tempFileName = strdup(fileNames[i]);
		
		printf("File Name: %s\n", tempFileName);
		
		if ((tempFile = fopen(tempFileName, "r")) == NULL) {
			fprintf(stderr, "could not allocate space");
			exit(-1);
		}
		
		long lengthOfFileName = strlen(tempFileName) + 1;
		
		printf("%d\n", lengthOfFileName);
		fwrite(&lengthOfFileName, sizeof(int), 1, outputFile);
		
		fwrite(tempFileName, sizeof(char), lengthOfFileName, outputFile);
		
		long tempSize = (fileSize(tempFile));
		printf("%d\n", tempSize);
		
		fwrite(&tempSize, sizeof(long), 1, outputFile);
		
		
	}
	fclose(outputFile);
	
}

//unarchive function
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
		
	}
}