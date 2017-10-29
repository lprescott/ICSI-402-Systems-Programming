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
#include "archivingSize.h"

/*
  This function checks to see if the given character array string is a flag. if it is, the program
  returns -1, else the function will return 1 and exit. It only takes one parameter, a char array that
  will be compared to known flags for the archiver program.
*/
int checkIfFlag(char * string){
  if(strcmp(string, "-a") == 0){
    //This would be a duplicate of the -a flag
    fprintf(stderr, "Multiple flags detected.\n");
    return -1;
  }
  else if(strcmp(string, "-u") == 0){
    //This would be a duplicate of the -u flag
    fprintf(stderr, "Multiple flags detected.\n");
    return -1;
  }
  else if(strcmp(string, "-v") == 0){
    //This would be a duplicate of the -v flag
    fprintf(stderr, "Multiple flags detected.\n");
    return -1;
  }
  else if(strcmp(string, "-l") == 0){
    //This would be a duplicate of the -l flag
    fprintf(stderr, "Multiple flags detected.\n");
    return -1;
  }
  else return 1;
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
	sscanf(string, "%ld", &number);

	return number;
}

/*
char ** appendString(char ** names, int length, char* string) {

	char ** tempCharArray = malloc((length + 2) * sizeof(char*));

	printf("GOT HERE");

	int i; //Counting int
	for (i = 0; i <= length; i++) {
		tempCharArray[i] = (char *)malloc(strlen(names[i])+1);
		//Check if fileName is too long.
		if (strlen(names[i]) >= sizeFileName){
			fprintf(stderr, "The file name would cause an overflow. ");
			exit(-1);
		}
		strcpy(tempCharArray[i], names[i]);
	}


	tempCharArray[i] = (char *)malloc(strlen(string)+1);
	strcpy(tempCharArray[i+1], string);

	int y;
    for (y = 0; y <= length; ++y){
        free(names[y]);
    }
    free(names);
}
*/


void archiveWithCap(char** fileNames, int numFiles, char* archiveName, long contentLimit) {

  //Loop to determine the number of bytes contained in each file, ordered in a array
  int bytesPerFile[numFiles], x = 0, totalBytes = 0;
  char * tempArchiveName = strdup(archiveName);

  char * tempString;
  FILE * tempFile = NULL;
  for(x; x<numFiles; x++){
    if ((tempFile = fopen(fileNames[x], "r")) == NULL) {
	    fprintf(stderr, "Could not allocate space for a new tempFile: %s.\n", fileNames[x]);
			exit(-1);
		}
    tempString = strdup(fileNames[x]);
    int currentBytes = 0;
    //Bytes for file name's length:
    //Currently: SIZElengthOfFileName
    currentBytes += SIZElengthOfFileName;

    //Bytes for file name
    //Currently: 1 + fileNames[x] length
    currentBytes += 1 + strlen(fileNames[x]);

    //Bytes for content size
    //Currently: S
    currentBytes += SIZElengthOfFile;

    //Bytes for contents
    //Currently fileSize([x]);
    currentBytes +=  fileSize(tempFile);

    //Store in bytesPerFile array
    bytesPerFile[x] = currentBytes;

    //Add to total
    totalBytes += currentBytes;

    //Close it
    fclose(tempFile);
  }

  printf("The total bytes of the supplied files: %d\n", totalBytes);

  int newBytesPerFile[numFiles]; //A integer array for the size of under limit files
  char * newFileNames[numFiles]; //A string array for the files under size limit
  x = 0; int y = 0; //X counts the outer forloop; Y counts one inner control structure
  for(x; x<numFiles; x++){
      if(bytesPerFile[x] + SIZEnumOfFilesInArchive > contentLimit){
        continue;
      }
      else{
        newBytesPerFile[y] = bytesPerFile[x];
        newFileNames[y] = malloc(strlen(fileNames[x]) + 1);
        strcpy(newFileNames[y], fileNames[x]);
        y++;
      }
  }

  printf("\nThe file(s) to be archived:\n");
  x = 0; 
  for(x; x<y; x++){
    printf("%d : %s : %d\n", x+ 1, newFileNames[x], newBytesPerFile[x]);
  }

  numFiles = y;

  int currentArchive = 1;
  //If files can fit in one archiveName
  if (totalBytes + SIZEnumOfFilesInArchive < contentLimit){
    archive(newFileNames, numFiles, addNumber(archiveName, currentArchive));
    
    printf("\n1 binfile was created.\n");

    return;
  }

  else{
    int bytesDifference = (totalBytes + SIZEnumOfFilesInArchive) - contentLimit;

    if (bytesDifference > 0){
      printf("\nThere are %d too many bytes to insert all in one bin file. So,\n", bytesDifference);
    }
  }

  //If there is one file, just add it
  if(numFiles == 1){
    char ** tempFilesNames = malloc(sizeof(char *));
    tempFilesNames[0] = malloc(strlen(newFileNames[0])+1);
    strcpy(tempFilesNames[0], newFileNames[0]);
    archive(tempFilesNames, 1, addNumber(archiveName, 1));
    free(tempFilesNames[0]);
    free(tempFilesNames);

    printf("1 binfile was created.\n");
    return;
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
    free(tempFilesNames);

    printf("2 binfiles were created.\n");

    return;
  }

  else if (numFiles > 2){
    //Create a new string array that has the maximum size of the number of files
    char ** tempFilesNames = malloc(numFiles * sizeof(char *));
    //There are more than two files, that need to be split correctly

    x = 0; int currentMemory = 0; y = 0; int currentfiles = 0;
    //int numberOfArchives = 0;
    while(x < numFiles){
      if (currentMemory + newBytesPerFile[x] + SIZEnumOfFilesInArchive < contentLimit){

        currentMemory += newBytesPerFile[x];
        currentfiles ++;

        tempFilesNames[currentfiles - 1] = malloc(strlen(newFileNames[x]) + 1);
        strcpy(tempFilesNames[currentfiles - 1], newFileNames[x]);

        //printf("\nCurrent mem: %d ",  currentMemory);
        ///printf("\nCurrent x: %d ", x);
        //printf("\nCurrent y: %d ", y);
        //printf("\nCurrent pos: %d ", currentfiles - 1);
        //printf("\nCurrent files: %d ", currentfiles);
        x++;
      }
      else{
        int p = 0;
        for(p; p < currentfiles; p++){
          free(tempFilesNames[p]);
        }

        currentMemory = 0;
        currentfiles = 0;
        y ++;
      }
      if(currentMemory != 0){
        printf("%s wrote to %s; total size: %d bytes.\n", newFileNames[x-1], addNumber(tempArchiveName, y + 1), currentMemory);
        archive(tempFilesNames, currentfiles, addNumber(archiveName, y+1));
      }
    }
  }

  else{
    fprintf(stderr, "Number of files is resulting in an error.\n");
    exit(-1);
  }

} //End archiveWithCap


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
      newName[length-1] = c;
      newName[length] = '\0';
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
    char * newName, tempName, * extension;
    //There is an extension
    if(currentArchive > 1){
        length = strlen(archiveName) + 1;
        newName = strdup(archiveName);
        //Change the number
        index = 0;
        
        strlength = strlen(newName);
        length = strlen(extension = strstr(newName, "."));
        pos = strchr(archiveName, '.');
        index = (int)(pos - archiveName);

        /*
        printf("The strlength: %d\n", strlength);
        printf("The length: %d\n", length);
        printf("The extension: %s\n", extension);
        printf("The index: %d\n", index);
        */
        
        c = currentArchive + '0';
        newName[strlength - length] = c;

        newName[index] = c;
        newName[index + 1] = '\0';

        strcat(newName, pos);
    }    
    else{
      //Find the pos before the extension and add the number 1
      length = strlen(archiveName) + 1;
      newName = malloc((length * sizeof(char)) + 1);
      c = currentArchive + '0';
      
      pos = strchr(archiveName, '.');
      //extension = strdup(pos);
      index = (int)(pos - archiveName);
      strncpy(newName, archiveName, index);
      //strcpy(newName, archiveName);
      newName[index] = c;
      newName[index + 1] = '\0';
      
      newName = strcat(newName, pos);
    }
  
    return newName;
    free(newName);
  }
} //End addNumber