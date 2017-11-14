//included libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//included headers
#include "other.h"
#include "BSTheaders.h"

//3. A C source file containing implemented functions that correspond to the prototypes in BSTheaders.h

/*
    This function takes the attributes of a instructionSet struct as parameters. Allocating memory for and 
    assigning for a newInstructionSet struct. Finally it returns a pointer to the new struct.
*/
instructionSet * newInstructionSet(char * instruction, unsigned char opcode, unsigned char format)
{
    //Allocate memory for the new struct and check if null
    instructionSet * newInstructionSet = (instructionSet *)malloc(sizeof(instructionSet));
    if(newInstructionSet == NULL){
        fprintf(stderr, "Could not allocate memory for newInstructionSet.\n");
        exit(1);
	}

    //Copy the supplied string 
	strcpy(newInstructionSet->instruction, instruction);

    //Assign the supplied numbers
	newInstructionSet->opcode = opcode;
	newInstructionSet->format = format;
    
    //Initialize the left and right pointers to NULL
    newInstructionSet->left = NULL;
    newInstructionSet->right = NULL;

    //Return the new struct
    return newInstructionSet;
}