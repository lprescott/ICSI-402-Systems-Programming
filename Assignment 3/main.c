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
#include "linkedList.h"

int main(int argc, const char * argv[]) {
	
	DIR * dr; //Directory to be used if given
	FILE * invid, * tempFile; //file to store the inverted index
	int i; //integer used for any for loops necessary in main function
	
	
	//////////////////////////////////////
	//TEST SPACE FOR LINKED LIST OBJECTS//
	//////////////////////////////////////
	//START
								//THIS THING INITIALIZES ALL VALUES IN A STRUCT TO NULL OR 0
		struct termList head = (const struct termList) { 0 };
		
		
		addTerm(&head, "aa");
		addTerm(&head, "aaaaa");
		addTerm(&head, "aaa");
		addTerm(&head, "aaaa");
		addTerm(&head, "b");
		addTerm(&head, "a");
		
		printAll(head);
		

		
		//add()
		
	//END
	
	
	//THIS BIG COMMENT IS WORKING CODE, JUST DOING LINKED LIST TESTING!!!!!!!
	//DO NOT DELETE THIS BIG COMMENT
	
	/*
	//Testing and printing all arguments, to be commented out later.
	printf("\nArguments given : \"%d\".\n\n", argc);
	for(i = 0; i < argc; i++) {
		printf("Argument %d : \"%s\".\n", (i + 1), argv[i]);
	}
	printf("\n");
	
	//If argc is greater than 3, the usr entered too many arguments, so the
	//program exits
	if (argc > 3) {
		fprintf(stderr, "ERROR: Entered too many arguments, exiting now\n\n");
		exit(-1);
	}
	//Case 1: Usr enters two arguments, open DIR dr and FILE invid
	if (argc == 3) {
		printf("User entered 2 arguments\n");
		//Case 1 1: Second argument is a directory
		if (isFile(argv[2])) {
			printf("\nSecond argument is a file, opening and indexing\n");
			
			
			//tempFile = fopen(argv[2], "r");
			//invid = fopen(argv[1], "w");
			//indexer(tempFile);
			
			
		} else if (isDir(argv[2])) {
			printf("\nSecond argument is a directory, opening and browsing\n");
			
			
			//invid = fopen(argv[1], "w");
			//dr = opendir(argv[2]);
			//browser(dr);
			
			
		} else {
			
			fprintf(stderr, "\nERROR: neither a file nor directory, exiting.\n");
			exit(-1);
			
		}
		
	}
	//Case 2: User enters one argument, open DIR dr and FILE invid as "invid.txt"
	if (argc == 2) {
		printf("User entered directory name, open inverted index as \"invid.txt\".\n");
		
			if (isFile(argv[1])) {
			printf("\nArgument is a file, opening and indexing\n");
			
			
			//tempFile = fopen(argv[2], "r");
			//invid = fopen(argv[1], "w");
			//indexer(tempFile);
			
			
		} else if (isDir(argv[1])) {
			printf("\nArgument is a directory, opening and browsing\n");
			
			
			//invid = fopen(argv[1], "w");
			//dr = opendir(argv[2]);
			//browser(dr);
			
			
		} else {
			
			fprintf(stderr, "\nERROR: neither a file nor directory, exiting.\n");
			exit(-1);
			
		}
		
	}
	
	//Case 3: No arguments, use current working directory and open FILE invid as "invid.txt"
	if (argc == 1) {
		printf("No user input, use current working directory and open inverted index as \"invid.txt\".\n");
		char currentDir[1024];
		if ((getcwd(currentDir, sizeof(currentDir))) == NULL) {
			
			fprintf(stderr, "\nERROR: Could not get current working directory, exiting\n");
			exit(-1);
			
		} 
		
		printf("Current Working Directory : \"%s\".\n", currentDir);
		
		
		//invid = fopen("invid.txt", "w");
		//dr = opendir(currentDir);
		//browser(dr);
		
		
	}
	
	//PrintContents(LIST);
	
	printf("\n");
	
	*/
	
}