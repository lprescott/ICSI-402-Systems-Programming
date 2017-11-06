
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"

int isFile(const char * path) {
	struct stat buf;
	stat(path, &buf);
	return S_ISREG(buf.st_mode);
}

int isDir(const char * path) {
	struct stat buf;
	stat(path, &buf);
	return S_ISDIR(buf.st_mode);
}

/*
addNumber returns a char * to the new augmented string that has been created by the supplied archive name and the current archive input,
the character to be inputted or changed.
*/
/*char * addNumber(char * archiveName, int currentArchive) {
	if (strstr(archiveName, ".") == NULL) {
		char * newName; char c; int length;
		char * tempName;

		//There is no extension
		if (currentArchive > 1) {
			//change the number
			length = strlen(archiveName) + 1;// value of the length is equal to the length the name of the archive +1
			newName = strdup(archiveName);// duplicate the name of archive into new name
			c = currentArchive + '0';
			newName[length - 1] = c;
			newName[length] = '\0';
			tempName = strdup(newName);// duplicates the newName into tempName
		}
		else {
			//add the number one
			length = strlen(archiveName) + 1; 1;// value of the length is equal to the length the name of the archive +1
			newName = malloc((length * sizeof(char)) + 1);//dynamic memory allocation
			c = currentArchive + '0';
			strcpy(newName, archiveName);// copy archiveName into newName
			newName[length - 1] = c;
			newName[length] = '\0';

			tempName = strdup(newName);// duplicates newName into tempName
			free(newName);// frees newName
		}
		return tempName;
	}
	else {


		char * pos; int index; char c; int length, strlength;// variable to position, the index, the length, and the string length
		char * newName, tempName, *extension;// variable for newName, the temp name, the extension
											 //There is an extension
		if (currentArchive > 1) {
			length = strlen(archiveName) + 1;
			newName = strdup(archiveName);
			//Change the number
			index = 0;

			strlength = strlen(newName);// gets the length of newName
			length = strlen(extension = strstr(newName, "."));
			pos = strchr(archiveName, '.');// searches for a . in the name of the archive, postion is set to that location
			index = (int)(pos - archiveName);
			c = currentArchive + '0';
			newName[strlength - length] = c;

			newName[index] = c;
			newName[index + 1] = '\0';

			strcat(newName, pos);// concatenates position with newName
		}
		else {
			//Find the pos before the extension and add the number 1
			length = strlen(archiveName) + 1;
			newName = malloc((length * sizeof(char)) + 1);// dynamic memory allocation allocation
			c = currentArchive + '0';

			pos = strchr(archiveName, '.');
			//extension = strdup(pos);
			index = (int)(pos - archiveName);
			strncpy(newName, archiveName, index);
			//strcpy(newName, archiveName);
			newName[index] = c;
			newName[index + 1] = '\0';

			newName = strcat(newName, pos);// conatenate pos with newName
		}

		return newName;
		free(newName);
	}
}*/

//This function takes a pointer to a head node of a list and a logline struct to add to said list as parameters.
//It returns a pointer to the head of the list which has been added to.

/*
loglist_t * addLast(loglist_t * list, logline_t templogline) {
	// Declare newStruct  here 
	loglist_t * newStruct = (loglist_t*)malloc(sizeof(loglist_t)); //The node to be added to the end of the list

																   //If there is no space then exit the program
	if (newStruct == NULL) {
		fprintf(stderr, "Failed to allocated memory newStruct.\n");
		exit(-1);
	}

	newStruct->line = templogline;
	newStruct->next = NULL;

	//check for first insertion
	if (list == NULL) {
		list = newStruct;
		return list;
	}
	else {
		//initalizes all the temp variables
		loglist_t * temp = list; // A temp loglist variable to use later on.

								 //loops to the end of the list
		while (temp->next != NULL) {
			temp = temp->next;
		}

		//adds the new node to the end of the list
		temp->next = newStruct;
		return list;
	}
}

/*

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
*/