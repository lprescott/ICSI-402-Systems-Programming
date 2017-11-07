
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

#include "structs.h"
#include "other.h"

void swap(termList * a, termList * b);

int isFile(const char * path) {
	struct stat s;
	stat(path, &s);
	return S_ISREG(s.st_mode);
}

int isDir(const char *file_path)
{
	struct stat s;
	stat(file_path, &s);
	return S_ISDIR(s.st_mode);
}

/*
  This function finds file size by seeking all the way to the end on the file, then telling the long
  position the position of the end character. This position is the size of the file in bytes. It only takes,
  one argument, which is the FILE type needed to point to.
*/
long fileSize(FILE * file){
    //Position: the variable to be returned, and the position of the end character.
    unsigned long endPosition = 0;
    unsigned long startPosition = 0;

    fflush(file); //Flush the buffer
    startPosition = ftell(file); //Record the start pos.

	// if it is null, and error is printed and terminates
    if (file == NULL){
        fprintf(stderr, "Error opening file in fileSize().\n");
        return(-1);
    }

    fseek(file, 0, SEEK_END);// sets the file position of the stream to the given offset

    endPosition = ftell(file);// ftell returns the current file postion of the given stream, and that is the value of position.

    fseek(file,startPosition,SEEK_SET); //return to start position

    return endPosition;// returns the position of the file offset
}

int isTermContained(char * termSupplied, termList * head){
	while (head != NULL){
		if (strcmp(termSupplied, head->term) == 0){
			return 1;
		}
		head = head->next;
	}
	return 0;
}

/*
	Function void deleteTermList, frees all memory allocated for the list. Takes the head of the list 
	as its only parameter.
*/
void deleteTermList(termList * head){
	//if head is equal to null, then return
	if (head == NULL){
		return;
	}
	
	//sets current equal to head
	termList * current = head;
	termList * next;
	
	//loops through the list, freeing up data for every variable until current hits null
	while (current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}
	head = NULL;
}

/*
	The function readFromFile returns a pointer to the head of a linked list of termList 
	structs. It accepts one parameter, the input file's absolute path. readFromFile reads through 
	the supplied file, adding the terms to the linked list, the file their from, and the correct count
	(incremented) when required.
*/
//termList * readFromFile(char * inputFilePath);

/*
	The function readFromIndex returns a pointer to the head of a linked list of termList 
	structs. It accepts two parameters, the FILE that is to be read from and its name for re-
	opening. readFromIndex reads through the supplied file, adding data in order to the linked 
	list when required.
*/
//termList * readFromIndex(FILE * outputFile, char * outputFileName);

/*
	The function sortTerms returns and takes a pointer to the head of a linked list of termList 
	structs. This function sorts the terms by alphabetical order.
*/
//termList * sortTerms(termList * inputList);

/*
	The function mergeSorted takes a pointer to two head nodes of termList structs, both are already 
	sorted. It then creates and returns a new pointer to the head of a new termList struct that contains values
	from both supplied linked lists in order.s
*/
//termList * mergeSorted(termList * inputList, termList * outputList);

/*
	The function printSorted returns nothing. It takes three parameter: One, a pointer to the head
	of a linked list that is to be printed in the correct format to the output file that is supplied as
	well - Two. Three, the name of the outputFile is supplied for reopening when required.
*/
//void printSorted(termList * inputList, FILE * outputFile, char * outputFileName);


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

/*
addNumber returns a char * to the new augmented string that has been created by the supplied archive name and the current archive input,
the character to be inputted or changed.
*/

/*
char * addNumber(char * archiveName, int currentArchive) {
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
}
*/