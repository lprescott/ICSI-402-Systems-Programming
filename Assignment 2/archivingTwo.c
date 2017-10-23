//Project: 	Prog1
//Names:   	Luke Prescott, Rob Rose, Tommy Li (lprescott@albany.edu, rwrose@albany.edu, tli3@albany.edu)
//Roles:   	Leader, Monitor, Recorder Respectively
//Date:    	10/19/2017
//Course:  	ICSI 402
//Desc:    	A function to handle the -l flag and a function to handle the - v flag.
//Input:
//Output:
//Assumption:

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "archivingTwo.h"
#include "other.h"
#include "constants.h"
#include "archivingSize.h"

// function to handle -l flag
/*
  This function takes the archiveName, and opens the archive. If the archive exists, this will
  print the total size of the archive file, the names of all the individual files in the archive,
  and their respectie sizes.
*/
void printArchiveDetails(char* archiveName) {
	
		//Variables here
	char * tempArchiveName;
	int numOfFiles, fileNameLength;
	long contentSize, totalSize;
	tempArchiveName = strdup(archiveName);
	FILE * inputFile;
	int fileDetectedCount = 0;
	
	// concatenate ".bin" to a temp archiveName string.
	if (strstr(tempArchiveName, ".bin") == NULL){
		strcat(tempArchiveName, ".bin");
	}

	//opens a new bin file with new string for reading
	if ((inputFile = fopen(tempArchiveName, "rb")) == NULL){
		fprintf(stderr, "Could not allocate space for the input archive.");
		exit(-1);
	}
	
	totalSize = fileSize(inputFile);
 
	printf("\nTotal Size of %s (in bytes): %d\n", tempArchiveName, totalSize);
 
	fread(&numOfFiles, sizeNumFiles, 1, inputFile);

	printf("\nNumber of Files: %d\n", numOfFiles);
	
	int i = 0;
	for (i = 0; i < numOfFiles; i++) {
		fread(&fileNameLength, sizeof(int), 1, inputFile);
		//printf("%d\n", fileNameLength);
		
		char * tempString = malloc(fileNameLength * sizeof(char));
		
		if (tempString == NULL) {
			exit(-1);
		}
		
		fread(tempString, sizeof(char), fileNameLength, inputFile);
		fread(&contentSize, sizeof(long), 1, inputFile);
		
		printf("File Name: %s; Size (in bytes): %d\n", tempString, contentSize);
		
		fseek(inputFile, contentSize, SEEK_CUR);
		
	}
	
	printf("\n");
	
} //End details

///function to handle -v flag
/*
  Takes the archiveName, and checks to see if all the fileNames are contained within the archive.
  If the archive correctly contains all the files, then "Archive verified" is printed to the console.
  If the archive is missing data, then the program will print "Archive is missing X bytes" to the console.
  If the archive's data is incorrect, then the program will print "Archive is corrupted."
*/
void verifyArchive(char ** fileNames, int numFiles, char * archiveName) {
		
//Variables
	char * tempArchiveName = strdup(archiveName);
	FILE * inputFile, * tempFile;
	long contentSizeArchive, contentSizeFile;
	int inputFileNameS, archiveFileNameS; //Size of the input file name and the archive file name respectively
	int index, archiveNumOfFiles;
	long missingBytes = 0;
	int fileDetectedCount = 0;
	
	// concatenate ".bin" to a temp archiveName string.
	if (strstr(tempArchiveName, ".bin") == NULL){
		strcat(tempArchiveName, ".bin");
	}

	//opens a new bin file with new string for writing
	if ((inputFile = fopen(tempArchiveName, "rb")) == NULL){
		fprintf(stderr, "Could not allocate space for the output archive.");
		exit(-1);
	}
	
	//peice of mind printing
	printf("\nNum Files to check %d: ", numFiles);
 
	//Reads in archive num of files, and passes the archive pointer
	fread(&archiveNumOfFiles, sizeof(int), 1, inputFile);
	printf("\nNumber of files given by .bin %d\n", archiveNumOfFiles);
	
	//For loop for the number of files of the archive
	int i;
	int y = 0;
	for (i = 0; i < archiveNumOfFiles; i++) {
		
		//getLength of FileName #i
		fread(&archiveFileNameS, sizeof(int), 1, inputFile);
		
		//printf("\narchiveFileNameS: %d\n", archiveFileNameS);
		
		char * tempString = malloc(archiveFileNameS * sizeof(char));
		if (tempString == NULL) {
			exit(-1);
		}
		
		fread(tempString, sizeof(char), archiveFileNameS, inputFile);
		//prints out fileNameArchive
		//printf("\n%s\n", tempString);
		
		//Compare the fileSize byte
		fread(&contentSizeArchive, sizeof(long), 1, inputFile);  
   
		if ((index = checkIfContains(fileNames, numFiles, tempString)) == -1) {
			fseek(inputFile, contentSizeArchive, SEEK_CUR);
			continue;
		}
		fileDetectedCount++;
		//Compare the file contents
		
		//printf("File Name: %s\n", fileNames[index]);
		
		if ((tempFile = fopen(fileNames[index], "r")) == NULL) {
			fprintf(stderr, "could not allocate space");
			exit(-1);
		}
		
		long count = 0;
		int cArchive;
		int cFile;
		
		while(count < contentSizeArchive) {
			//Compare each char
			
			cArchive = fgetc(inputFile);
			cFile = fgetc(tempFile);
			count++;
			
			if (cArchive != cFile) {
				printf("\nArchive is Corrupted\n");
				return;
			}
			
		}
		
		contentSizeFile = fileSize(tempFile);
		
		printf("\n%d %d\n", contentSizeFile, count);
		
		if (contentSizeFile != count) {
			missingBytes += (contentSizeFile - count);
		}
		
		//necessary freeing and closing
		fclose(tempFile);
		free(tempString);
	}
	
	if (missingBytes != 0) {
		printf("\nArchive is missing %d bytes.\n", missingBytes);
		return;
	}
	
	if (fileDetectedCount < numFiles) {
		printf("\nArchive is missing an unknown amount of bytes.\n");
	}
	
	printf("\nArchive Verified\n");
	
}