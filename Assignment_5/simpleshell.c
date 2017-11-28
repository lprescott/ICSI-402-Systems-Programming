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
    char * commandline; //This temporary string holds one commandline from the shell or script
    char * command; //The first word in the commandline, the command.

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
        while((commandline = getLine(script)) != NULL){
            printf("\"%s\"\n", commandline);
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
        printf("simpleshell:~$ ");
        //Loop to read cmd-line line by line
        while((commandline = getLine(stdin)) != NULL){

            command = strtok(commandline, " ");

            //Check if command should quit simpleshell, then exit with (1)
            if(strcmp(command, "quit") == 0){
                printf("goodbye\n");
                exit(1);
            }
            else if(strcmp(command, "create") == 0){
                
            }
            else if(strcmp(command, "wd") == 0){
                
            }
            else if(strcmp(command, "chwd") == 0){
                
            }
            else if(strcmp(command, "fileconverter") == 0){
                
            }
            else{
                fprintf(stderr, "ERROR: Invalid command.\n");
            }

            //Print shell name for next command
            printf("simpleshell:~$ ");
        }
    }

} //End int main( int argc, char *argv[] )