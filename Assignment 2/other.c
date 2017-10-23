//Project: 	Prog1
//Names:   	Luke Prescott, Rob Rose, Tommy Li (lprescott@albany.edu, rwrose@albany.edu, tli3@albany.edu)
//Roles:   	Leader, Monitor, Recorder Respectively
//Date:    	10/19/2017
//Course:  	ICSI 402
//Desc:    	// this contains additional functions needed for the functionality of the main.c file


#include <stdio.h>
#include <string.h>

#include "other.h"
#include "constants.h"

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
			printf("\n index Given : %d", i);
			return i;
		}
	}
    
    //If nothing else it returns -1
	return -1;
}
