//Project: 	Prog3
//Names:   	Luke Prescott, Rob Rose, Tommy Li (lprescott@albany.edu, rwrose@albany.edu, tli3@albany.edu)
//Roles:   	Leader, Monitor, Recorder Respectively
//Date:    	11/9/2017
//Course:  	ICSI 402
//Desc:    	Given a set of files, the program parses the files and creates an inverted index, which maps each
//			term found in the files to the subset of files that contain that term. 
//        	
//Input:   	The program can take a command line arguments specifying the path where the program will execute
//	   		otherwise, it will execute in the current directory; the program also takes a command line arg.
//			specifying the name of the outputted file. 
//Output:  	A file containing the inverted index.
//Assumption:	The possible command line argument is assumed to be a unix path to a directory in unix.

//Inluded headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>

#include "structs.h"
#include "index.h"
#include "browse.h"
#include "other.h"

/*
		This is the main function of the indexer program. It's control structures determines the 
	directory for opening, looks through said directory for files, reads lines of any  file, using
	indexer, it finds and then proceeds to add them to a linked list in a linked list of said file. 
	That is, the main function call indexer, and browser depending on the user input indexing the
	file, if supplied, or all files in the directory, if supplied in a inverted index.
*/
int main(int argc, const char * argv[]) {
	
	//Variables
	FILE * invInd; //file to store the inverted index
	int i; //integer used for any for loops necessary in main function
	char * defaultName = "invind.txt"; //The default name of the output file

	//Testing and printing all arguments, to be commented out later.
	printf("\nArguments given : \"%d\".\n", argc);
	for(i = 0; i < argc; i++) {
		printf("Argument %d : \"%s\".\n", (i + 1), argv[i]);
	}
	printf("\n");
	
	//If argc is greater than 3, the user entered too many arguments, so the
	//program exits
	if (argc > 3) {
		fprintf(stderr, "ERROR: Entered too many arguments, exiting now.\n");
		exit(-1);
	}
	//Case 1: User enters two arguments
	if (argc == 3) {
		char * tempName = strdup(argv[1]); //Duplicate the outputfile name for use
		FILE * invID = fopen(tempName, "a"); //Opens the outputfile, its supplied name, for appending
		char ** listOfFiles; //declares a list of string that holds all files to use
		listOfFiles = malloc(sizeof(char *)); //Allocates memory for first pointer

		if (isFile(argv[2])) {
			printf("\nSecond argument is a file, opening and indexing.\n");
			listOfFiles[0] = strdup(argv[2]);
			//indexer(listOfFiles, invID, 1);
		} else if (isDir(argv[2])) {
			printf("\nSecond argument is a directory, browsing, opening and indexing.\n");
			//listOfFiles = browse(argv[2]);
			//int numofFiles = listLength(listOfFiles);
			//indexer(listOfFiles, invID, numOfFiles);
		} else {	
			fprintf(stderr, "\nERROR: neither a file nor directory, exiting.\n");
			exit(-1);
			
		}

		fclose(invID);
		free(listOfFiles);
		
	}
	//Case 2: User enters one argument, open DIR dr and FILE invid as "invid.txt"
	if (argc == 2) {
		printf("User has entered one argument, open inverted index as \"invid.txt\".\n");

		FILE * invID = fopen(defaultName, "a"); //Openes default file for appending
		char ** listOfFiles; //declares a list of string that holds all files to use
		listOfFiles = malloc(sizeof(char *)); //Allocates memory for first pointer
		
		if (isFile(argv[1])) {
			printf("\nArgument is a file, opening and indexing.\n");
			listOfFiles[0] = strdup(argv[1]);
			//indexer(listOfFiles, invID, 1);
			
		} else if (isDir(argv[1])) {
			printf("\nArgument is a directory, browsing, opening and indexing.\n");
			//listOfFiles = browse(argv[1]);
			//int numofFiles = listLength(listOfFiles);
			//indexer(listOfFiles, invID, numOfFiles);
			
		} else {
			fprintf(stderr, "\nERROR: neither a file nor directory, exiting.\n");
			exit(-1);
			
		}
		
		fclose(invID);
		free(listOfFiles);
	}
	
	//Case 3: No arguments, use current working directory and open FILE invid as "invid.txt"
	if (argc == 1) {
		printf("No user input, use current working directory and open inverted index as \"invid.txt\".\n");
		char currentDir[1024]; //declare a string for the current dir path
		FILE * invID = fopen(defaultName, "a"); //open the default file name for appending
		char ** listOfFiles; //declares a list of string that holds all files to use
		listOfFiles = malloc(sizeof(char *)); //Allocates memory for first pointer

		if ((getcwd(currentDir, sizeof(currentDir))) == NULL) {
			fprintf(stderr, "\nERROR: Could not get current working directory, exiting.\n");
			exit(-1);	
		} 
		
		printf("Current Working Directory : \"%s\".\n", currentDir);
	
		//listOfFiles = browse(currentDir);
		//int numofFiles = listLength(listOfFiles);
		//indexer(listOfFiles, invID, numOfFiles);

		fclose(invID);
		free(listOfFiles);
	
	}
}
