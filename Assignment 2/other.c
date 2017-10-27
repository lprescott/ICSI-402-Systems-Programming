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

char *  addNumber(char * archiveName, int currentArchive);

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
			return number;
		}
	}

	//Converts string and puts the value into number
	//printf("%d, is the number", number);
	sscanf(string, "%d", &number);

	return number;
}

void archiveWithCap(char** fileNames, int numFiles, char* archiveName, long contentLimit) {

  //Loop to determine the number of bytes contained in a each file, ordered in a array
  int bytesPerFile[numFiles], x = 0;
  char * tempArchiveName = strdup(archiveName);

  char * tempString;
  FILE * tempFile = NULL;
  for(x; x<numFiles; x++){
    if ((tempFile = fopen(fileNames[x], "r")) == NULL) {
	    fprintf(stderr, "Could not allocate space for a new tempFile.");
			exit(-1);
		}
    tempString = strdup(fileNames[x]);
    int currentBytes = 0;
    //Bytes for file name's length:
    //Currently: SizeOfFileLength
    currentBytes += SizeOfFileLength;

    //Bytes for file name
    //Currently: 1 + fileNames[x] length
    currentBytes += 1 + strlen(fileNames[x]);

    //Bytes for content size
    //Currently SizeOfTheFile
    currentBytes += SizeOfTheFile;

    //Bytes for contents
    //Currently fileSize([x]);
    currentBytes += fileSize(tempFile);

    //Store in bytesPerFile array
    bytesPerFile[x] = currentBytes;

    //Close it
    fclose(tempFile);
  }

  int newBytesPerFile[numFiles];
  char * newFileNames[numFiles];
  x = 0; int y = 0;
  for(x; x<numFiles; x++){
      if(bytesPerFile[x] > contentLimit){
        continue;
      }
      else{
        newBytesPerFile[y] = bytesPerFile[x];
        newFileNames[y] = malloc(strlen(fileNames[x]) + 1);
        strcpy(newFileNames[y], fileNames[x]);
        y++;
      }
  }

  printf("\nThe files to be archived:\n");
  x = 0; int totalBytes = 0;
  for(x; x<y; x++){
    totalBytes += newBytesPerFile[x];
    printf("%d ; %d ; ", x + 1, newBytesPerFile[x]);
    printf("%s\n", newFileNames[x]);
  }

  numFiles = x;
  printf("The total bytes of the supplied files: %d\n", totalBytes);

  int currentArchive = 1;
  //If files can fit in one archiveName
  if (totalBytes < contentLimit){
    archive(newFileNames, numFiles, addNumber(archiveName, currentArchive));
  }
  else{
    int bytesDifference = totalBytes - contentLimit;
    printf("There are %d too many bytes to insert in one bin file.\n", bytesDifference);
  }

  //If there is one file, just add it
  if(numFiles == 1){
    char ** tempFilesNames = malloc(sizeof(char *));
    tempFilesNames[0] = malloc(strlen(newFileNames[0])+1);
    strcpy(tempFilesNames[0], newFileNames[0]);
    archive(tempFilesNames, 1, addNumber(archiveName, 1));
    free(tempFilesNames[0]);

    printf("One binfile was created.\n");
  }

  //If there are two files, just split them
  else if (numFiles == 2){
    char ** tempFilesNames = malloc(sizeof(char *));
    tempFilesNames[0] = malloc(strlen(newFileNames[0])+1);
    strcpy(tempFilesNames[0], newFileNames[0]);
    archive(tempFilesNames, 1, addNumber(archiveName, 1));

    free(tempFilesNames[0]);
    tempFilesNames[0] = malloc(strlen(newFileNames[1])+1);
    strcpy(tempFilesNames[0], newFileNames[1]);
    archive(tempFilesNames, 1, addNumber(archiveName, 2));
    free(tempFilesNames[0]);

    printf("Two binfiles were created.\n");
  }

  else if (numFiles > 2){
    //Create a new string array that has the maximum size of the number of files
    char ** tempFilesNames = malloc(numFiles * sizeof(char *));
    //There are more than two files, that need to be split correctly

    x = 0; int currentMemory = 0; y = 0; int currentfiles = 0;
    //int numberOfArchives = 0;
    while(x < numFiles){
      if (currentMemory + newBytesPerFile[x] < contentLimit - 4){

        currentMemory += newBytesPerFile[x];
        currentfiles ++;

        tempFilesNames[currentfiles - 1] = malloc(strlen(newFileNames[x]) + 1);
        strcpy(tempFilesNames[currentfiles - 1], newFileNames[x]);

        //printf("\nCurrent mem: %d ",  currentMemory);
        printf("\nCurrent x: %d ", x);
        printf("\nCurrent y: %d ", y);
        printf("\nCurrent pos: %d ", currentfiles - 1);
        printf("\nCurrent files: %d ", currentfiles);
        x++;
      }
      else{
        printf("Reset.");

        int p = 0;
        for(p; p < currentfiles; p++){
          free(tempFilesNames[p]);
        }

        currentMemory = 0;
        currentfiles = 0;
        y ++;
      }
      if(currentMemory != 0){
        printf("\nAdd %d bytes to %d bin file.", currentMemory, y);
        archive(tempFilesNames, currentfiles, addNumber(archiveName, y+1));
      }
    }

    free(tempFilesNames);
    printf("\n");
  }

  else{
    fprintf(stderr, "Number of files is resulting in an error.\n");
    exit(-1);
  }
}

char * addNumber(char * archiveName, int currentArchive){
  if(strstr(archiveName, ".") == NULL){
    char * newName; char c; int length;
    char * tempName;

    //There is no extension
    if(currentArchive > 1){
      //change the number
      length = strlen(archiveName) + 1;
      newName = strdup(archiveName);
      c = currentArchive + '0';
      newName[length-2] = c;
      tempName = strdup(newName);
    }
    else{
      //add the number one
      length = strlen(archiveName) + 1;
      newName = malloc((length * sizeof(char)) + 1);
      c = currentArchive + '0';
      strcpy(newName, archiveName);
      newName[length-1] = c;
      newName[length] = '\0';

      tempName = strdup(newName);
      free(newName);
    }
    return tempName;
  }
  else{
    char * pos; int index; char c; int length, strlength;
    char * newName, tempName, extension;
    //There is an extension
    if(currentArchive > 1){
        length = strlen(archiveName) + 1;
        newName = malloc((length * sizeof(char)));
        strcpy(newName, archiveName);
        //Change the number

        strlength = strlen(newName);
        length = strlen(strstr(newName, ".")) + 1;
        //printf("%d %d", strlength, length);

        c = currentArchive + '0';

        newName[strlength - length] = c;

    }
    else{
      //Find the pos before the extension and add the number 1

    }

    return newName;
    free(newName);
  }
}
