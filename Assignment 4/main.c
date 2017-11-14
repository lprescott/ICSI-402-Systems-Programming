//1. A C source file with just the main function.

//included libraries
#include <stdio.h>
#include <stdlib.h>

//included headers
#include "other.h"
#include "BSTheaders.h"
#include "hashHeaders.h"

//main method
int main( int argc, char *argv[] )  {
	//variables
	int hashTableSize = 0; //an integer to hold the hash table size supplied
	
	//Check number of arguments
	if(argc < 4){
		fprintf(stderr, "There were only %d arguments supplied. Expected 4.\nExiting...\n", argc);
		exit(-1);
	}
	else if(argc > 4){
		fprintf(stderr, "There were %d arguments supplied. Expected 4.\nExiting...\n", argc);
		exit(-1);
	}
	else{
		//Print out supplied arguments
		printf("\nfirstpass has been called.\n");
		printf("The supplied instructionset filename: \"%s\".\n", argv[1]);
		printf("The supplied programfile filename: \"%s\".\n", argv[2]);
		printf("The supplied hashtablesize: %s.\n", argv[3]);
	}
	
	//Check if the supplied hashtablesize is not a number
	if(atoi(argv[3]) == 0){
		fprintf(stderr, "\nThe supplied hashtablesize is not a number.\nExiting...\n");
		exit(-1);
	}

	//Assign int to converted command line arg.
	hashTableSize = atoi(argv[3]);

	//Check if the instructionset file doesn't exists or is unreadable
	if(fileExistsAndReadable(argv[1])==0){
		fprintf(stderr, "\nThe supplied instructionset filename, \"%s\", cannot be opened or cannot be read.\nExiting...\n", argv[1]);
		exit(-1);
	}

	//Check if the programfile file doesn't exists or is unreadable
	if(fileExistsAndReadable(argv[2])==0){
		fprintf(stderr, "\nThe supplied programfile filename, \"%s\", cannot be opened or cannot be read.\nExiting...\n", argv[2]);
		exit(-1);
	}

	//Check if the supplied hashtablesize is not atleast 2
	if(hashTableSize < 2){
		fprintf(stderr, "\nThe supplied hashtablesize is not atleast 2.\nExiting...\n");
		exit(-1);
	}

	printf("\nDone.\n");
}
