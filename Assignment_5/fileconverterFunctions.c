#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "fileconverterFunctions.h"

/*

*/
void convertToReadable(char * inputFileName, char * outputFileName) {
    FILE * binFILE; //FILE pointer to hold binary file 
    FILE * txtFILE; //FILE pointer to hold text file 
    
    //Temporary variables to hold student record 
    unsigned char templ1;
	unsigned char templ2;
	char * tempfirstName;
	char * templastName;
	int tempid;
	int tempGPA;
    
    studentRecord tempRecord; //Temporary studentRecord struct

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
        
    }


    //Close files
    fclose(binFILE);
    fclose(txtFILE);
}

/*

*/
void convertToBinary(char * inputFileName, char * outputFileName) {
	
}

/*

*/
void printDetails(char * inputFileName) {
	
}
