//Project: 	Prog1
//Names:   	Luke Prescott, Rob Rose, Tommy Li (lprescott@albany.edu, rwrose@albany.edu, tli3@albany.edu)
//Roles:   	Leader, Monitor, Recorder Respectively
//Date:    	10/19/2017
//Course:  	ICSI 402
//Desc:    	// this contains additional functions needed for the functionality of the main.c file
//Input:
//Output:
//Assumption:

#include <stdio.h>
#include <string.h>

#include "other.h"
#include "constants.h"

/*
  This function checks to see if the given character array string is a flag. if it is, the program
  returns -1, else the function will return 1 and exit.
*/
int checkIfFlag(char * string){
    if(strcmp(string, "-a") == 0){
        fprintf(stderr, "Multiple flags detected. ");
        return -1;
    }
    else if(strcmp(string, "-u") == 0){
        fprintf(stderr, "Multiple flags detected. ");
        return -1;
    }
    else if(strcmp(string, "-v") == 0){
        fprintf(stderr, "Multiple flags detected. ");
        return -1;
    }
    else if(strcmp(string, "-l") == 0){
        fprintf(stderr, "Multiple flags detected. ");
        return -1;
    }

    return 1;
}

//loops through entire array, and if name is == fileNames the function returns the index, else it returns -1;
int checkIfContains(char ** fileNames, int numFiles, char * name) {
	
	//i for loop
	int i;
	
	for (i = 0; i < numFiles; i++) {
		if (strcmp(fileNames[i], name) == 0) {
			printf("\n index Given : %d", i);
			return i;
		}
	}
	
	return -1;
}
