#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"

/*
    This function reads one line from the specified file and returns the result as a null terminated string.
*/
char* getLine(FILE * stream){
    
    //lineSize is the maximum size of a line, and line is a pointer to the start of the read line
    const size_t lineSize = 1024;
    char * line = malloc(lineSize);

    //newLine is a char * to the line without the '\n' character 
    char * newLine;

    //Gets one line from stream, returning NULL if empty
    if (fgets(line, lineSize, stream)!= NULL){
        //Check if it ends with a newline, then replaces it with a terminator
        if(line[strlen(line)-1] == '\n'){
            line[strlen(line)-1] = '\0';

            //Free and return
            newLine = strdup(line);
            free(line);
            return newLine;
        }
        //Otherwise, just leave it be
        else{
            //Free and return
            newLine = strdup(line);
            free(line);
            return newLine;
        }
    }
    //fgets returned NULL
    else{
        //Free and return
        free(line);
        return NULL;
    }

} //End char* getLine(FILE * stream)

/*
	This function returns a 1 if the supplied file name exists  by using the access function. 
	If the supplied file name does not exist, the function returns 0.
*/
int fileExists(char * filename){
	//F_OK is used for checking if the file is readable
	if(access(filename, F_OK) != -1) return 1;
	else return 0;
} //End int fileExists(char * filename)

/*
	This function returns a 1 if the supplied file name is readable by using the access function. 
	If the supplied file name is not readable, the function returns 0.
*/
int fileReadable(char * filename){
	//R_OK is used for checking if the file is readable
	if(access(filename, R_OK) != -1) return 1;
	else return 0;
} //End int fileReadable(char * filename)