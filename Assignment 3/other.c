#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <ctype.h>

#include "structs.h"
#include "other.h"
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
		if(next = NULL){
			free(current);
			//free(current->filesAndCounts);
			return;
		}
		free(current);
		//free(current->filesAndCounts);
		current = next;
	}
	//head = NULL;
}


void printAll(struct termList ** head) {
	termList * current = *head;
	fileCountList * currentFile;
	int i = 1;
	while (current != NULL) {
		printf("\nTerm %d : \"%s\".\n", i, current->term);
		currentFile = current->filesAndCounts;
		while (currentFile != NULL) {
			printf("File %s : %d\n", currentFile->file, currentFile->count);
			currentFile = currentFile->next;
		}
		current = current->next;
		i++;
	}
}

void insertTerm(termList ** head, char * term, fileCountList * filesAndCounts){

	printf("Called insertTerm on : ");
	
	termList * current;
	termList * prev;
	termList * newNode;
	
	newNode = malloc(sizeof(termList));
	if(newNode == NULL){
		fprintf(stderr, "Could not allocate memory for termList * newNode.\n");
		exit(-1);
	}

	newNode->term = malloc(strlen(term) * sizeof(char));
	strcpy(newNode->term, term);
	/*
	newFileCount = malloc(sizeof(fileCountList));
	if(newFileCount == NULL){
		fprintf(stderr, "Could not allocate memory for fileCountList * newFileCount.\n");
		exit(-1);
	}

	newFileCount->file = malloc(strlen(tempFileName) * sizeof(char));
	strcpy(newFileCount->file, tempFileName);
	newFileCount->count = 1;
	*/
	newNode->filesAndCounts = filesAndCounts;

	printf("File: \"%s\" ; Term: \"%s\" ; Count %d.\n", filesAndCounts->file, newNode->term, filesAndCounts->count);

	//Head is equal to null, assign it new node
	if (*head == NULL) {

		printf("\t\t\t...inserted at head\n"); fflush(stdout);
		*head = newNode;
		newNode->next = NULL;
		return;
	}

	//If the new term goes before or is equal to head
	if (strcmp(term, (*head)->term) <= 0) {
		//The new term is equal to the head
		if (strcmp(term, (*head)->term) == 0) {
			//DO INCREMENT
			//printf("INCREMENTING %s on term %s\n", (*head)->term, term);
			printf("\t\t\t...incremented at head\n"); fflush(stdout);
			fileCountList * current;
			current = (*head)->filesAndCounts;
			
			//Increment count in head if contains same file
			while(current != NULL) {
				if (strcmp(current->file, filesAndCounts->file) == 0) {
					current->count++;
					return;
				}
				current = current->next;
			}

		} 
		//The term is inserted before the head
		else {
			printf("\t\t\t...inserted before head\n"); fflush(stdout);
			newNode->next = *head;
			*head = newNode;
		}
		return;
		
	}

	//Inserting or incrementing in body
	current = (*head);
	while (current != NULL) {
		if (strcmp(term, (current)->term) <= 0) {
		
			if (strcmp(term, (current)->term) == 0) {
				//DO INCREMENT
				//printf("INCREMENTING (In Loop) %s on term %s\n", (current->term), term);
				printf("\t\t\t...incremented in body\n");
				fileCountList * currentFile;
				currentFile = current->filesAndCounts;
				
				while(currentFile != NULL) {
					if (strcmp(currentFile->file, filesAndCounts->file) == 0) {
						currentFile->count++;
						return;
					}
					currentFile = currentFile->next;
				}
				
			} 
			else {
				printf("\t\t\t...inserted in body\n");
				newNode->next = current;
				prev->next = newNode;
				return;
			}

		}
		
		prev = current;
		current = current->next;
	}

	current = (*head);
	while(current->next != NULL){
		current = current->next;
	}
	
	current->next = newNode;
	newNode->next = NULL;
	printf("\t\t\t...added on end.\n");
}

int isEmpty(const char *s) {
  while (*s != '\0') {
    if (!isspace((unsigned char)*s))
      return 0;
    s++;
  }
  return 1;
}

/*
	The function readFromFile returns a pointer to the head of a linked list of termList 
	structs. It accepts one parameter, the input file's absolute path. readFromFile reads through 
	the supplied file, adding the terms to the linked list, the file their from, and the correct count
	(incremented) when required.
*/
termList * readFromFile(char * inputFilePath) {

	printf("\t\tAttempting to read from file \"%s\".\n", inputFilePath);
	printf("\t\tFile contents: \n");

	FILE * inputFile = fopen(inputFilePath, "r");
	if(inputFile == NULL){
		fprintf(stderr, "Could not allocate space for: %s.\n", inputFilePath);
		exit(-1);	
	}
	char line[1024]; char * token;
	int i; 
	
	termList * head = NULL;

	while(fgets(line, 1024, inputFile) != NULL){
		printf("\t\t\t%s", line);
	}

	printf("\n");
	
	rewind(inputFile);

	char * currentFile;
	int x = 0, count = 0;

	for(x; x < strlen(inputFilePath) + 1; x++){
		if(inputFilePath[x] == '/'){
			count ++;
		}
	}

	currentFile = strstr(inputFilePath, "/");

	for(x = 0; x < count; x ++){
		currentFile = strstr(currentFile, "/");
		++currentFile;
	}

	printf("\t\tCurrent file: \"%s\".\n", currentFile);

	printf("\t\tFormatted file contents: \n");

	while(fgets(line, 1024, inputFile) != NULL){
		if (isEmpty(line)) continue;

		for (i = 0; i < strlen(line); i++) {
			
			if (!isalnum(line[i])) {
				line[i] = ' ';
			}
			
		}

		printf("\t\t%s\n", line);
		
		token = strdup(line);
		token = strtok(token, " ");
		
		fflush(stdout);
		printf("\t\t\tTerms: \n");
		
		int j;
		while(token) {

			for(j = 0; token[j]; j++){
				token[j] = tolower(token[j]);  
			}

			printf("\t\t\t\"%s\" ", token);
			
			fileCountList * newFileCount = malloc(sizeof(fileCountList));
			if(newFileCount == NULL){
				fprintf(stderr, "Could not allocate memory for fileCountList * newFileCount.\n");
				exit(-1);
			}

			newFileCount->file = malloc(strlen(currentFile) * sizeof(char));
			strcpy(newFileCount->file, currentFile);
			newFileCount->count = 1;
			
			insertTerm(&head, token, newFileCount);
			token = strtok(NULL, " ");
			
		}

		printf("\n");
	}

	fclose(inputFile);
	return head;

}

printAllCount(fileCountList ** head) {
	fileCountList * current = *head;
	printf("It is here!\n");
	while(current != NULL) {
		printf("File Name: %s %d\n", current->file, current->count);
		current = current->next;
	}
}

/*
	The function readFromIndex returns a pointer to the head of a linked list of termList 
	structs. It accepts two parameters, the FILE that is to be read from and its name for re-
	opening. readFromIndex reads through the supplied file, adding data in order to the linked 
	list when required.
*/

void deleteFileCountList(fileCountList ** head) {
	
	fileCountList * tmp;
	
	while (head == NULL) {
		
		tmp = (*head);
		(*head) = (*head)->next;
		free(tmp);
		
	}
	
}

termList * readFromIndex(char * outputFileName){
	printf("\t\tAttempting to read from file \"%s\".\n", outputFileName);
	
	FILE * inputFile = fopen(outputFileName, "r");
	if (inputFile == NULL) {
		exit(-1);
	}
	char line[1024];
	char * token;
	char * tempTerm;
	char * end1;
	char * tempFileName;
	int tempCount;
	
	termList * head = NULL;
	
	fileCountList * fileCountHead = NULL;
	
	while (fgets(line, 1024, inputFile) != NULL) {
		token = strdup(line);
		token[strlen(token) - 1] = '\0';
		//printf("\t\t\tLINE : %s\n", token);
		
		token = strtok_r(token, " ", &end1);
				
		if (strcmp(token, "<list>") == 0) {
			
			token = strtok_r(NULL, " ", &end1);
			tempTerm = strdup(token);
			
			printf("\n\t\t\tList start, \"%s\" is the term.\n", tempTerm);
			
			continue;
			
		}
		
		if (strcmp(token, "</list>") == 0) {
			
			printf("\t\t\tList End, insert in head list\n");
			
			printAllCount(&fileCountHead);
			
			insertTerm(&head, tempTerm, fileCountHead);
			
			deleteFileCountList(&fileCountHead);
			fileCountHead = NULL;
			
			continue;
			
		}
		
		printf("\t\t\t\tList : ");
		
		while (token) {
			
			tempFileName = strdup(token);
			
			token = strtok_r(NULL, " ", &end1);
			
			int count = atoi(token);
			
			fileCountList * newNode = malloc(sizeof(fileCountList));
			
			if (newNode == NULL) {
				fprintf(stderr, "ERROR IN readFromIndex: could not allocate newNode\n");
				exit(-1);
			}
			
			newNode->file = malloc(strlen(tempFileName) * sizeof(char));
			strcpy(newNode->file, tempFileName);
			newNode->count = count;
			
			printf("\n\t\t\t\t\"File name : %s, count : %d\" \n", newNode->file, newNode->count); fflush(stdout);
			token = strtok_r(NULL, " ", &end1);
			
			insertFileAndCount(&fileCountHead, newNode);
		
		}
		
		printf("\n");
		
	}
	
	printAll(&head);
	
	return head;
	
	//printf("\n");
	
}

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
void printSorted(termList * inputList, char * outputFileName){
	FILE * outputFile;

	//This erases the current outputFile
	outputFile = fopen(outputFileName, "w");
	if(outputFile == NULL){
		fprintf(stderr, "Could not allocate memory for: %s.\n", outputFileName);
	}

	termList * temp;
	temp = inputList;

	while(temp!=NULL)
	{
		fprintf(outputFile, "<list> %s\n", temp->term);
		fileCountList * tempFileCount;
		tempFileCount = temp->filesAndCounts;
		while(tempFileCount != NULL){
			fprintf(outputFile, "%s %d ", tempFileCount->file, tempFileCount->count);
			tempFileCount = tempFileCount->next;
		}
		fprintf(outputFile, "\n");
		fprintf(outputFile, "</list>\n");
		temp=temp->next;
	}

	fclose(outputFile);

}

void insertFileAndCount(fileCountList ** head, fileCountList * tempNode){

	if (*head == NULL) {
		//printf("\t\t\t\t... %s inserting into head\n", tempNode->file);
		*head = malloc(sizeof(fileCountList));
		*head = tempNode;

		return;
	}
	
	if ((*head)->count < tempNode->count) {
		//printf("\t\t\t\t... %s replacing head");
		tempNode->next = *head;
		*head = tempNode;
		
		return;
	}
	
	//printf("\t\t\t\t... %s inserting into list\n", tempNode->file);
	
	fileCountList * current = *head;
	fileCountList * prev;
	
	while(current != NULL) {
		if (current->count < tempNode->count) {
			prev->next = tempNode;
			tempNode->next = current;
		}
		prev = current;
		current = current->next;
	}
	prev->next = tempNode;
	
	
}



