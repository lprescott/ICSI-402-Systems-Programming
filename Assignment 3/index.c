#include <stdio.h>
#include <stdlib.h>

#include "index.h"
#include "other.h"
#include "structs.h"
/*
    The indexer function returns nothing, but takes two arguments as parameters: the absolute path of an input file to added to the supplied FILE * to the
    output file. This function reads data from outputFile, adds data to outputFile, sorts said data and rewrites is back to the outputFile. 
*/
void indexer(char * inputFilePath, FILE * outputFile, char * outputFileName){
    //If the outputFile is empty
    if (fileSize(outputFile) == 0){
        printf("\tThe output file is empty!\n");

        termList * inputList;
        termList * outputList;

        inputList = malloc(sizeof (termList));
        if (inputList == NULL){
            fprintf(stderr, "Could not allocate memory for inputList.");
        }

        outputList = malloc(sizeof (termList));
        if (outputList == NULL){
            fprintf(stderr, "Could not allocate memory for outputList.");
        }

        //Read data into memory
        //Sort data in memory
        //Print sorted data to outputFile

        free(inputList);
        free(outputList);
    }
    
    //If the outputFile is not empty
    else{
        printf("\tThe output file is NOT empty!\n");

        termList * inputList;
        termList * outputList;

        inputList = malloc(sizeof (termList));
        if (inputList == NULL){
            fprintf(stderr, "Could not allocate memory for inputList.");
        }

        outputList = malloc(sizeof (termList));
        if (outputList == NULL){
            fprintf(stderr, "Could not allocate memory for outputList.");
        }


        //Read sorted data into memory
        //Read non-sorted data into memory
        //MergeSort latter into former
        //Rewrite new merged list into outputFile

        free(inputList);
        free(outputList);
    }
}