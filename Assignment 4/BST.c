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

void insertBST(instructionSet ** head, instructionSet * newNode) {
	
	//if head == null, set head = to newNode and then return;
	if ((*head) == NULL) {
		*head = newNode;
		return;
	}
	/*
		If the heads instruction is less that newNodes instruction, then
		insert newNode into the heads LEFT node, else insert it into the 
		heads RIGHT node.
	*/
	if (strcmp((*head)->instruction, newNode->instruction) >= 0) {
		insertBST(&(*head)->left, newNode);
		return;
	} else {
		insertBST(&(*head)->right, newNode);
		return;
	}
	
}

//function to print the BST(binary search tree) inorder, takes a parameter named currentNode of the struct instructionSet

void printInOrder(instructionSet * currentNode) {
	
	//if current node is NULL
	if (currentNode == NULL) {
		return;
	}
	
	//checks the left child node
	printInOrder(currentNode->left);
	
	//prints the data of that node
	printf("%s, ", currentNode->instruction);
	
	 //check the right child node
	printInOrder(currentNode->right);
	
}


unsigned char searchOpcodeBST(instructionSet * currentNode, char instruction[6]) {
	
	//if current node is NULL
	if (currentNode == NULL) {
		return NULL;
	}
	
	if (strcmp(currentNode->instruction, instruction) == 0) {
		return currentNode->opcode;
	}
	
	//checks the left child node
	if (strcmp(currentNode->instruction, instruction) < 0) {
		return searchOpcodeBST(currentNode->right, instruction);
	} else {
		return searchOpcodeBST(currentNode->left, instruction);
	}
	
}

unsigned char searchFormatBST(instructionSet * currentNode, char instruction[6]) {
	
	//if current node is NULL
	if (currentNode == NULL) {
		return NULL;
	}
	
	if (strcmp(currentNode->instruction, instruction) == 0) {
		return currentNode->format;
	}
	
	//checks the left child node
	if (strcmp(currentNode->instruction, instruction) < 0) {
		return searchFormatBST(currentNode->right, instruction);
	} else {
		return searchFormatBST(currentNode->left, instruction);
	}
	
}

int maxHeight(instructionSet * currentNode) {
	
	if (currentNode == NULL) {
		return 0;
	}
	
	int leftHeight = maxHeight(currentNode->left);
	int rightHeight = maxHeight(currentNode->right);
	
	if (leftHeight > rightHeight) {
		return (leftHeight + 1);
	} else {
		return (rightHeight + 1);
	}
	
}