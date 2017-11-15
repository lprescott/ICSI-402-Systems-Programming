//5. A C source file containing implemented functions that correspond to the prototypes in hashHeaders.h.

//included libaries
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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

void insertHash(hashNode ** head, hashNode * newNode) {
	printf("\tAttempting insert on symbol : \"%s\"\n", newNode->symbol); fflush(stdout);
	//pointers for current and previous
	hashNode * current;
	hashNode * prev;
	
	//if head == NULL set head = to new node
	if ((*head) == NULL) {
		printf("\t\tHead is null...\n"); fflush(stdout);
		*head = newNode;
		return;
	}
	
	printf("\t\thead is not null...\n"); fflush(stdout);
	//If head is not null, insert head at the end of the list
	current = (*head);
	while (current != NULL) {
		//printf("looping...\n"); fflush(stdout);
		prev = current;
		//printf("This is the seg fault?\n"); fflush(stdout);
		prev = current;
		current = current->next;
	}
	printf("\t\tHit end...\n"); fflush(stdout);
	prev->next = newNode;
	
}

/*
This function takes a array of linked lists (hashTable) and its array size as parameter and returns nothing. It prints each inner 
linked list in the form:
    index: listNode1 → listNode2 → · · · → listNodeN → NULL.
*/
void printHashTable(int size, hashNode * hashTable[]){
    int i = 0; //Index needed for the loop
    
    //Loop through every element in the array
    for(i; i < size; i++){
        
        //if the head of the linked list is null
        if(hashTable[i] == NULL){
            printf("\n%d:\n", i);
        }
        //else the linked list has values
        else{
            printf("\n%d: ", i);
            hashNode * tempNode; //a tempNode used for traversal
            tempNode = hashTable[i]; //assign the tempNode to the current head of the linked list at index i
            //loop through and print the enture linked list
            while(tempNode != NULL){
                printf("%s - %d → ", tempNode->symbol, tempNode->address);
                tempNode = tempNode->next;
            }
            printf("NULL");
        }
    }
}
