//1. A C source file with just the main function.

//included libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//included headers
#include "other.h"
#include "BSTheaders.h"
#include "hashHeaders.h"

//Constants
#define LINESIZE 100

//main method
int main( int argc, char *argv[] )  {
	//variables
	int hashTableSize = 0; //an integer to hold the hash table size supplied
	FILE * instructionSetFile; //A FILE type for the instructionSet input file
	FILE * programFile; //A FILE type for the program input file
	char line [LINESIZE]; //A char pointer that will store each line in the instructionSet input file
	char tempInstruction [6]; //The temp five character long instruction
	unsigned char tempOpcode; //The temp unsigned char to hold the opcode integer 
	unsigned char tempFormat; //The temp unsigned char to hold the format integer
	char * token; //A char pointer used when tokenizing a line in the instructionSetFile
	instructionSet * head = NULL; //A instructionSet pointer to the head node of the used BST
	instructionSet * tempNode; //A instructionSet pointer to the head node of the temp BST node

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

	//Open and check the instructionset filename
	instructionSetFile = fopen(argv[1], "r");
	if(instructionSetFile == NULL){
        	fprintf(stderr, "Could not allocate memory for instructionSetFile.\nExiting...\n");
        	exit(1);
	}

	printf("\n");
	//Parse line by line, inserting into BST
 	while (fgets(line, LINESIZE, instructionSetFile)) {
		tempNode = NULL; //Set the tempNode to NULL at every loop

		//Parse (and print) the lines of the instructionSetFile
		//printf("%s", line);
		token = strdup(line);

		//The instruction is the line up to the first space
		token = strtok(token, " ");
		strcpy(tempInstruction, token);
		//printf("%s ", tempInstruction);

		//The opcode is the rest of the line up to the second space
		token = strtok(NULL, " ");
		tempOpcode = atoi(token);
		//printf("%d ", tempOpcode);

		//The format is the rest of the line up to the newline char
		token = strtok(NULL, "\n");
		tempFormat = atoi(token);
		//printf("%d\n", tempFormat);

		//create tempNode
		tempNode = newInstructionSet(tempInstruction, tempOpcode, tempFormat);

		//print attributes of tempNode
		printf("%s ", tempNode->instruction);
		printf("%d ", tempNode->opcode);
		printf("%d\n", tempNode->format);
		
		//Insert tempNode into head
		insertBST(&head, tempNode);
		
		
	}

	//Print the BST (in-order)
	printf("\n");
	printInOrder(head);
	printf("\b\b \n");
	
	//Print the max height
	printf("Max Height : \"%d\"\n", maxHeight(head));
	
	printf("Opcode of 'ldb' : %u\n", searchOpcodeBST(head, "ldb")); fflush(stdout);
	printf("Format of 'sta' : %u\n", searchFormatBST(head, "sta"));
	
	//Close opened files and print done
	fclose(instructionSetFile);
	printf("\nDone.\n");
}
