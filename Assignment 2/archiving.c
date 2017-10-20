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
	if ((outputFile = fopen(tempArchiveName, "w")) == NULL){
		fprintf(stderr, "Could not allocate space for the output archive.");
		exit(-1); 
	}
	
	//print #of files to bin
	fwrite(&tempNumOfFiles, sizeNumFiles, 1, outputFile);

	//loop for numFiles through string array
	for(int i = 0; i < numFiles; i++){
		char * tempFileName;
		tempFileName = strdup(fileNames[i]);
		printf("\nHITTING A LOOP\n");
		//open file
		printf("The file name is: \"%s\"", tempFileName);
		if ((tempFile = fopen(tempFileName, "r")) == NULL){
			fprintf(stderr, "Could not allocate space for a temp intput file. ");
			exit(-1); 
		}

		//get, store, print size of fileName
		int lengthOfFileName = strlen(tempFileName);
		fwrite(&lengthOfFileName, sizeLengthFile, 1, outputFile);

		//get, store, print the fileName
		fwrite(&tempFileName, lengthOfFileName, 1, outputFile);

		//get, store, print size of contents( use fileSize() function here)
		long sizeOfContents = fileSize(tempFile);
		fwrite(&sizeOfContents, sizeFileSize, 1, outputFile);

		//get, store , print the contents
		rewind(tempFile);
		int c = fgetc(tempFile);
		while (c != EOF){
			//puts("ADDING ");
			fwrite(&c, sizeof(c), 1, outputFile);
			c = fgetc(tempFile);
		}

		//close tempFile
		fclose(tempFile);
	}
	//close outputFile
	fclose(outputFile);

}

//unarchive function
void unarchive(char* archiveFile) {
        
//declare temp string including archiveName
//concatenate .bin into an archiveName
//open archive, open for reading only
//read first 4 bytes(#of files)
/*
a.for loop for # of files
b.read next 1 bytes(determines length of filename to be created)
c. for loop for length of name
d.open newfile of temp string
e.read next 4 bytes for content size
f.adding it to the file, in the loop of the content size
g. close tempfile
*/
//close bin file
}
