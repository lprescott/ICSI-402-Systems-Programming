#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileconverterFunctions.h"
/*

*/
void convertToReadable(char * inputFileName, char * outputFileName) {
	
}

/*

*/
void convertToBinary(char * inputFileName, char * outputFileName) {
	
	fflush(stdout);
	FILE * inputFile, * outputFile;
	char line[1024];
	char * token;
	char * firstName;
	char * lastName;
	char * id; int ID; 
	char * gpa; int GPA;
	unsigned char l1, l2;
	
	//checks if inputFile could be opened
	if ((inputFile = fopen(inputFileName, "r")) == NULL) {
		fprintf(stderr, "ERROR could not open input file.\n");
		exit(-1);
	}
	
	//checks if outputFile could be opened
	if ((outputFile = fopen(outputFileName, "w")) == NULL) {
		fprintf(stderr, "ERROR could not open outputFile file.\n");
		exit(-1);
	}
	
	//While line != null parse each line
	while (fgets(line, sizeof(line), inputFile) != NULL) {
		
		//Gets rid of the newline character
		if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
		printf("%s\n", line);
		
		//duplicates token into line
		token = strdup(line);
		
		token = strtok(token, " ");
		
		while (token) {
			//gets firstName and parses l1
			firstName = strdup(token);
			l1 = (unsigned char)strlen(firstName);
			printf("%s %u\n", firstName, l1);
			
			token = strtok(NULL, " ");
			
			//gets lastName and parses l2
			lastName = strdup(token);
			l2 = (unsigned char)strlen(lastName);
			printf("%s %u\n", lastName, l2);
			
			token = strtok(NULL, " ");
			
			//gets id
			id = strdup(token);
			ID = atoi(id);
			printf("%d\n", ID);
			
			token = strtok(NULL, " ");
			
			//gets GPA
			gpa = strdup(token);
			GPA = atoi(gpa);
			printf("%d\n", GPA);
			
			token = strtok(NULL, " ");
			
		}
		
		//writes all necessary variables to gpa
		fwrite(&l1, sizeof(l1), 1, outputFile);
		fwrite(firstName, sizeof(char), l1, outputFile);
		fwrite(&l2, sizeof(l2), 1, outputFile);
		fwrite(lastName, sizeof(char), l2, outputFile);
		fwrite(&ID, sizeof(ID), 1, outputFile);
		fwrite(&GPA, sizeof(GPA), 1, outputFile);
		
		printf("\n");
		
	}
	
}

/*

*/
void printDetails(char * inputFileName) {
	
}