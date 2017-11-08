#include <stdlib.h>

#include "structs.h"

int isFile(const char * path);
int isDir(const char * path);
long fileSize(FILE * file);

int isTermContained(char * termSupplied, termList * head);
void deleteTermList(termList * head);

void insertTerm(termList ** head, char * term, fileCountList * filesAndCounts);
termList * readFromFile(char * inputFilePath);
termList * readFromIndex(char * outputFileName);
termList * sortTerms(termList * inputList);
termList * mergeSorted(termList * inputList, termList * outputList);
void printSorted(termList * inputList, char * outputFileName);


//char * addNumber(char * archiveName, int currentArchive);

/*
void insertAtFirst(char * term, termList * head);
void addTerm(termList * head, char * term);
void printAll(struct termList * head);
*/