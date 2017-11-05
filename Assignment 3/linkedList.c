#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"

void insertAtFirst(char * term, termList * head) {
	termList * newNode;
	newNode = malloc(sizeof(termList));
	newNode->term = malloc(strlen(term) * sizeof(char));
	strcpy(newNode->term, term);
	
	newNode->next = head;
	head = newNode;
}

void addTerm(termList * head, char * term) {
	
	//Create newNode to be added
	termList * prev;
	termList * current;
	termList * newNode;
	
	if (head->term == NULL) {
		
		printf("Head is null, Adding \"%s\" to head.\n", term);
		
		head->term = malloc(strlen(term) * sizeof(char));
		strcpy(head->term, term);
		
		//printf("REACHED HERE : HEAD TERM %s\n", head->term);
		
		return;
		
	}
	
	//THE CULPRIT FOR NOT ADDING TO THE FIRST NODE, IF TERM IS BEFORE HEAD->TERM, ADD DIRECTLY TO THE FRONT OF THE LIST
	if (strcmp(term, head->term) < 0) {
		newNode = malloc(sizeof(termList));
		newNode->term = malloc(strlen(term) * sizeof(char));
		strcpy(newNode->term, term);
		
		newNode->next = head;
		head = newNode;
		return;
	}
		

	//Purely for testing purposses
	int index = 0;
	current = head;
	printf("Head is not null, Adding \"%s\" to list.\n", term);
	
	//Adds objects too the list in alphabetical order
	while (current != NULL) {
		printf("Index %d\n", index);
		//If the term is less than or equal to current->term, then add term to prev->next
		if (strcmp(term, current->term) <= 0) {
			printf("We add this term Here\n");

			prev->next = malloc(sizeof(termList));
			prev->next->term = malloc(strlen(term) * sizeof(char));
			strcpy(prev->next->term, term);
			prev->next->next = current;
			return;
			}
			
		}
		//Incrememnts both prev and current
		prev = current;
		current = current->next;
		index++;
	}
	//If this item is the largest, add to end of list with prev->next
	prev->next = malloc(sizeof(termList));
	prev->next->term = malloc(strlen(term) * sizeof(char));
	strcpy(prev->next->term, term);
	
}

void printAll(struct termList * head) {
	termList * current = head;
	int i = 1;
	while (current != NULL) {
		printf("Term %d : \"%s\".\n", i, current->term);
		current = current->next;
		i++;
	}
}