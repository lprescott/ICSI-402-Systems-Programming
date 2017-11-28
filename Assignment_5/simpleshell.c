//Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Headers
#include "input.h"

/*

*/
int main( int argc, char *argv[] )  {

    //Variables
    FILE * script; //This pointer to a file contained a script to be executed in-order
    char * command; //This temporary string holds one command from the shell or script

    if( argc == 2 ) {
        //One command line argument
        //Start shell on supplied script-file
        
        //Check if the instructionset file doesn't exists or is unreadable
	    if(fileExists(argv[1])==0){
	    	fprintf(stderr, "\nThe supplied instructionset filename, \"%s\", does not exist.\nExiting...\n", argv[1]);
		    exit(-1);
	    }
	    if(fileReadable(argv[1])==0){
	    	fprintf(stderr, "\nThe supplied instructionset filename, \"%s\", cannot be read.\nExiting...\n", argv[1]);
	    	exit(-1);
        }
        
        //Open the script-file (and check if fopen returns NULL)
        if ((script = fopen(argv[1], "r")) == NULL){
            fprintf(stderr, "Could not allocate memory for \"%s\".\nExiting...\n", argv[1]);
            exit(-1);   
        }

        //Print for script-file
        printf("Script-file: (w/ added newlines)\n");

        //Loop to read script-file line by line
        while((command = getLine(script)) != NULL){
            printf("\"%s\"\n", command);
        }

        //Close the script-file
        fclose(script);
    }
    else if( argc > 2 ) {
        //More than one command line argument
        fprintf(stderr, "A wrong number of command line arguments were provided to simpleshell.c.\nExiting...\n");
        exit(-1);
    }
    else {
        //No command line arguments
        //Start shell on command line
        
        //Print shell name for first command
        printf("simpleshell$ ");
        //Loop to read cmd-line line by line
        while((command = getLine(stdin)) != NULL){
            //printf("\"%s\"\n", command);

            //Check if commands should quit simpleshell, then exit with (1)
            if(strcmp(command, "quit") == 0){
                printf("goodbye\n");
                exit(1);
            }

            //Print shell name for next command
            printf("simpleshell$ ");
        }
    }

} //End int main( int argc, char *argv[] )