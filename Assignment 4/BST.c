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

/*this function checks the max height of BST(binary search tree),
 takes a parameter named currentNode that is a pointer to the struct instructionSet
 */
int maxHeight(instructionSet * currentNode) {
	
	if (currentNode == NULL) {
		return 0;
	}
	
	// computes the height of each sub
	int leftHeight = maxHeight(currentNode->left);
	int rightHeight = maxHeight(currentNode->right);
	
	/* if the left height is greater than right height return the height of the left increased by one
	else return the height of the right increased by 1*/
	if (leftHeight > rightHeight) {
		return (leftHeight + 1);
	} else {
		return (rightHeight + 1);
	}
	
}