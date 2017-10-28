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
  and their respective sizes. it takes parameters archiveName.
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
	//makes totalSize equal to fileSize that takes a parameter named inputFile
	totalSize = fileSize(inputFile);
        //prints the total size of the entire archive
	printf("\nTotal Size of %s (in bytes): %d\n", tempArchiveName, totalSize);
        //reads number of files from the .bin file
	fread(&numOfFiles, sizeNumFiles, 1, inputFile);

	printf("\nNumber of Files: %d\n", numOfFiles);
	//for loop, that loops through the file.
	int i = 0;
	for (i = 0; i < numOfFiles; i++) {
		fread(&fileNameLength, sizeof(int), 1, inputFile);
		//printf("%d\n", fileNameLength);
		//dynamic memory allocation for the name of the file
		char * tempString = malloc(fileNameLength * sizeof(char));
		//checks if you can't allocate, then terminates
		if (tempString == NULL) {
			exit(-1);
		}
		//reads the file name into tempString
		fread(tempString, sizeof(char), fileNameLength, inputFile);
		//reads the content size from the .bin file.
		fread(&contentSize, sizeof(long), 1, inputFile);
		// prints the filename and the size
		printf("File Name: %s; Size (in bytes): %d\n", tempString, contentSize);
		//seeks to the next file
		fseek(inputFile, contentSize, SEEK_CUR);

		//free
		free(tempString);

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
	char * tempArchiveName = strdup(archiveName);// char pointer to the name of the archive
	FILE * inputFile, * tempFile;// file pointers to inputfile and tempfile
	long contentSizeArchive, contentSizeFile;// size of the content and size of the file
	int inputFileNameS, archiveFileNameS; //Size of the input file name and the archive file name respectively
	int index, archiveNumOfFiles;// index of the filename and number of file in archive
	long missingBytes = 0;// number of missing bytes
	int fileDetectedCount = 0;// counts of the appropriate number of files was detected.

	//opens a new bin file with new string for writing
	if ((inputFile = fopen(tempArchiveName, "rb")) == NULL){
		fprintf(stderr, "Could not allocate space for the output archive.");
		exit(-1);
	}


	//printf("\nNum Files to check %d: ", numFiles);

	//Reads in the archive num of files, and passes the archive pointer
	fread(&archiveNumOfFiles, sizeof(int), 1, inputFile);
	//printf("\nNumber of files given by .bin %d\n", archiveNumOfFiles);

	//Determine if there is a missing number of bytes
	if(numFiles == archiveNumOfFiles){
		//The same amount of files are supplied that are in the archive

		//Calculate the bytes in the archive
		long totalArchiveSize = fileSize(inputFile);
		char * tempString;
		int bytesPerFile[numFiles], x = 0;
		//Calculate the bytes in the files
		for(x; x<numFiles; x++){
			if ((tempFile = fopen(fileNames[x], "r")) == NULL) {
				fprintf(stderr, "Could not allocate space for a new tempFile.");
					exit(-1);
				}
			tempString = strdup(fileNames[x]);
			int currentBytes = 0;
			//Bytes for file name's length:
			//Currently: 4 bytes
			currentBytes += 4;

			//Bytes for file name
			//Currently: 1 + fileNames[x] length
			currentBytes += 1 + strlen(fileNames[x]);

			//Bytes for content size
			//Currently 4 bytes
			currentBytes += 4;

			//Bytes for contents
			//Currently fileSize([x]);
			currentBytes +=  fileSize(tempFile);

			//Store in bytesPerFile array
			bytesPerFile[x] = currentBytes;

			//Close it
			fclose(tempFile);
		  }

		  x = 0; long totalBytes;
		  for(x; x<numFiles; x++){
			totalBytes += bytesPerFile[x];
		  }

		  printf("fileSize(archive) = %ld\n", totalArchiveSize);
		  printf("loop for files = %ld\n", totalBytes + 5);
		//Subtract the difference

		int missingBytes = (totalBytes + 5) - totalArchiveSize;
		if (missingBytes != 0){
			printf("The archive is missing %d bytes.\n", missingBytes);
			return;
		}
	}
	else{
		//Less than the number of files in the archive
		//Calculate the bytes in the archive
		long totalArchiveSize = fileSize(inputFile);
		char * tempString;
		int bytesPerFile[numFiles], x = 0; long totalBytes = 0;
		//Calculate the bytes in the files
		for(x; x<numFiles; x++){
			if ((tempFile = fopen(fileNames[x], "r")) == NULL) {
				fprintf(stderr, "Could not allocate space for a new tempFile.");
					exit(-1);
				}
			tempString = strdup(fileNames[x]);
			int currentBytes = 0;
			//Bytes for file name's length:
			//Currently: 4 bytes
			currentBytes += 4;

			//Bytes for file name
			//Currently: 1 + fileNames[x] length
			currentBytes += 1 + strlen(fileNames[x]);

			//Bytes for content size
			//Currently 4 bytes
			currentBytes += 4;

			//Bytes for contents
			//Currently fileSize([x]);
			currentBytes +=  fileSize(tempFile);

			//Store in bytesPerFile array
			bytesPerFile[x] = currentBytes;

			//Close it
			fclose(tempFile);
			}

			x = 0;
			for(x; x<numFiles; x++){
			totalBytes += bytesPerFile[x];
			}

			int filesInArchive;


			//printf("The number of bytes in the supplied files: %d\n", totalBytes + 5);
			//printf("The size of the archive is: %d\n", fileSize(inputFile));

			fread(&filesInArchive, sizeof(int), 1, inputFile);
			//printf("The number of files in the archive is: %d\n", filesInArchive);

			int tempNameLength, sizeOfRest = 4, contentsToSeek, contentSize;
			x = 0;

			for(x; x < filesInArchive; x ++){
				fread(&tempNameLength, sizeof(int), 1, inputFile);
				sizeOfRest += 4;
				//printf("The temp name length; %d\n", tempNameLength);

				char * tempName = malloc(tempNameLength * sizeof(char));
				if (tempName == NULL) {
					exit(-1);
				}

				fread(tempName, sizeof(char), tempNameLength, inputFile);
				sizeOfRest += tempNameLength;

				printf("\n%s\n", tempName);

				fread(&contentSize, sizeof(long), 1, inputFile);
				printf("%d\n", contentSize);
				sizeOfRest += 4;

				if ((checkIfContains(fileNames, numFiles, tempName)) != -1){
					sizeOfRest -= 4;
					sizeOfRest -= tempNameLength;
					sizeOfRest -= 4;


					fseek(inputFile, contentSize, SEEK_CUR);
					continue;
				}

				sizeOfRest += contentSize;

			}



			int calculatedSize = sizeOfRest + totalBytes;
			printf("The size: %d", sizeOfRest);

			int diffrence = totalArchiveSize - calculatedSize ;
			printf(" \n%d\n", totalArchiveSize);

			if (diffrence != 0) {

				printf("The archive is missing %d bytes\n", diffrence);
				return;

			}

	}

	rewind(inputFile);
	//For loop for the number of files of the archive
	int i;
	int y = 0;
	for (i = 0; i < archiveNumOfFiles; i++) {

		//getLength of FileName #i
		fread(&archiveFileNameS, sizeof(int), 1, inputFile);

		//printf("\narchiveFileNameS: %d\n", archiveFileNameS);
		// dynamic memory allocation for the tempString
		char * tempString = malloc(archiveFileNameS * sizeof(char));
		if (tempString == NULL) {
			exit(-1);
		}
		//reads into tempString
		fread(tempString, sizeof(char), archiveFileNameS, inputFile);
		//prints out fileNameArchive
		//printf("\n%s\n", tempString);

		//reads in the content size
		fread(&contentSizeArchive, sizeof(long), 1, inputFile);

		//If tempString is contained in fileNames, go on, if not, move the file pointer and continue.
		if ((index = checkIfContains(fileNames, numFiles, tempString)) == -1) {
			fseek(inputFile, contentSizeArchive, SEEK_CUR);
			continue;
		}
		//comment files detected.
		fileDetectedCount++;
		//Compare the file contents

		//printf("File Name: %s\n", fileNames[index]);
		//Open tempFile
		if ((tempFile = fopen(fileNames[index], "r")) == NULL) {
			fprintf(stderr, "could not allocate space");
			exit(-1);
		}

		long count = 0;
		int cArchive;
		int cFile;

		while(count < contentSizeArchive) {
			//Compare each char, if char is diffrent print corrupted and then return

			cArchive = fgetc(inputFile);
			cFile = fgetc(tempFile);
			count++;

			if (cArchive != cFile) {
				printf("\nArchive is Corrupted\n");
				return;
			}

		}

		//get the fileSize of tempFile
		contentSizeFile = fileSize(tempFile);

		//printf("\n%d %d\n", contentSizeFile, count);

		//if contentSizeFile != count, add to missing bytes. If it isn't, move on.
		if (contentSizeFile != count) {
			missingBytes += (contentSizeFile - count);
		}

		//necessary freeing and closing
		fclose(tempFile);
		free(tempString);
	}

	fclose(inputFile);

	printf("\nArchive Verified\n");

}
