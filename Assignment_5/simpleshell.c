//Libraries
#include <stdio.h>
#include <stdlib.h>

//Headers
#include "input.h"

/*

*/
int main( int argc, char *argv[] )  {

    //Variables
    FILE * script;

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
    }

} //End int main( int argc, char *argv[] )