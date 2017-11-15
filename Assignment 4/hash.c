//5. A C source file containing implemented functions that correspond to the prototypes in hashHeaders.h.

//included libaries
#include <string.h>
#include <stdio.h>

//included headers
#include "hashHeaders.h"

/*
    This function takes the attributes of a hashNode struct as parameters. Allocating memory for and 
    assigning for a newHashNode struct. Finally it returns a pointer to the new struct.
*/
hashNode * newHashNode(char symbol[11], int address){

    //Allocate memory for the new struct and checks if null, if NULL, prints errors and terminates
    hashNode * newHashNode = (hashNode *)malloc(sizeof(hashNode));
    if(newHashNode == NULL){
        fprintf(stderr, "Could not allocate memory for newInstructionSet.\n");
        exit(1);
	}

    //Copy the supplied string 
	strcpy(newHashNode->symbol, symbol);

    //Assign the supplied number
	newHashNode->address = address;
    
    //Initialize the next pointers to NULL
    newHashNode->next = NULL;

    //Return the new struct
    return newHashNode;
}
