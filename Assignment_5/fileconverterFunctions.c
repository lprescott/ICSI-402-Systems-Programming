
//Project: 	Prog5
//Names:   	Luke Prescott, Rob Rose, Tommy Li (lprescott@albany.edu, rwrose@albany.edu, tli3@albany.edu)
//			(001252879, 001247373, 001209184)
//Roles:   	Leader, Monitor, Recorder Respectively
//Date:    	11/28/2017
//Course:  	ICSI 402

/*Desc: this file contains the necessary functions associated with the fileconverter command.
 This file contains the following functions convertToReadable, and convertToBinary, and printDetails
*/

//standard c libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//included external header files containing prototypes
#include "fileconverterFunctions.h"

/*
the convertToReadable function takes parameters of two char pointers named inputFileName, and outputFileName
the role of this function to is convert the inputted binary file to text file that is readable.

*/
void convertToReadable(char * inputFileName, char * outputFileName) {
    FILE * binFILE; //FILE pointer to hold binary file 
    FILE * txtFILE; //FILE pointer to hold text file 
    
    //Temporary variables to hold student record attributes
    unsigned char templ1;
	unsigned char templ2;
	char * tempfirstName = malloc(sizeof(char *));
	char * templastName = malloc(sizeof(char *));
	int tempid;
	int tempGPA;
    
    //Check if files are openable
    binFILE = fopen(inputFileName, "rb");
    if(binFILE == NULL){
        fprintf(stderr, "Could not allocate memory for the binFILE.\n");
        exit(-1);
    }

    txtFILE = fopen(outputFileName, "w");
    if(binFILE == NULL){
        fprintf(stderr, "Could not allocate memory for the txtFILE.\n");
        exit(-1);
    }

    //Loop to read through binary file
    while(1){
		if (fread(&templ1, sizeof(templ1), 1, binFILE) == 0) return; //read l1
        tempfirstName = malloc(sizeof(char) * templ1 + 1); //Allocate mem for first name
        if (fread(tempfirstName, sizeof(char), templ1, binFILE) == 0) return; //read tempfirstName
        if (fread(&templ2, sizeof(templ2), 1, binFILE) == 0) return; //read l2
        templastName = malloc(sizeof(char) * templ2 + 1); //Allocate mem for last name
        if (fread(templastName, sizeof(char), templ2, binFILE) == 0) return; //read templastName
        if (fread(&tempid, sizeof(tempid), 1, binFILE) == 0) return; //read tempid
        if (fread(&tempGPA, sizeof(tempGPA), 1, binFILE) == 0) return; //read tempGPA

		tempfirstName[templ1] = '\0';
		templastName[templ2] = '\0';

		//Print attributes to txt file
		printf("%d %s %d %s %d %d\n", templ1, tempfirstName, templ2, templastName, tempid, tempGPA);
        fprintf(txtFILE, "%s %s %d %d\n", tempfirstName, templastName, tempid, tempGPA);

        //Free strings
        free(tempfirstName);
        free(templastName);
    }
    
    //Close files
    fclose(binFILE);
    fclose(txtFILE);
}

/*
the convertToBinary function takes paramaters of two char pointers named inputFileName and outputFileName,
the role of this function to convert any text files that are in readable format to a binary format.
*/
void convertToBinary(char * inputFileName, char * outputFileName) {
	
	fflush(stdout);
	FILE * inputFile, * outputFile;// file pointers for the input and output files that are supplied
	char line[1024];// max size of the line
	char * token;// string named token
	char * firstName;// string that holds's the student's first name
	char * lastName;// string that holds's the student's last name
	char * id; int ID;// string that hold the students id number and a int that holds the value of the student id number
	char * gpa; int GPA;// string that hold the students gpa and a int that holds the value of the student's gpa
	unsigned char l1, l2;
	
	//checks if inputFile could be opened, if it can open it for reading, otherwise print error, and terminates
	if ((inputFile = fopen(inputFileName, "r")) == NULL) {
		fprintf(stderr, "ERROR could not open input file.\n");
		exit(-1);
	}
	
	//checks if outputFile could be opened, if it can open it for writing to binary, otherwise print error and terminates
	if ((outputFile = fopen(outputFileName, "wb")) == NULL) {
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
			ID = atoi(id);// converts a string to an int
			printf("%d\n", ID);// prints the value of the student's id
			
			token = strtok(NULL, " ");
			
			//gets GPA
			gpa = strdup(token);
			GPA = atoi(gpa);//converts a string to an int
			printf("%d\n", GPA);// prints the value of the student's gpa
			
			token = strtok(NULL, " ");
			
		}
		
		/*
		firstName[strlen(firstName)-1] = '\0';
		lastName[strlen(lastName)-1] = '\0';
		*/

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
