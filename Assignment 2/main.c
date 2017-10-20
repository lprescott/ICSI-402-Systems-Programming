/**
 * Project: Prog2
 * Names:   	Luke Prescott, Rob Rose, Tommy Li (lprescott@albany.edu, rwrose@albany.edu, tli3@albany.edu)
 * Roles:   	Leader, Monitor, Recorder Respectively
 * Date:    	10/19/2017
 * Course:  	ICSI 402
 * Desc:         This program is a modified .tar archiving tool, used to create and unpack .tar file.
 * Input:        A command line argument with the commands -a, -u, -l, -v.
 *              -a archivename file1 file2 ... fileN:  creates an archive with the specified name and files given after the command.
 *	            -u archivename:                        Unpacks an archive with the given name.
 *	            -l archivename:                        Print to stdout the names and total size of the archive and each file.
 *	            -v archivename file1 file2 ... fileN:  determines weather or not the specified archive is damaged
 * output:       Depends on the command
 * assumption:   The user will give one and only one command while calling archiver 
**/

//Included libraries:
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>

//Included header files:
#include "constants.h"
#include "archiving.h"
#include "archivingSize.h"
#include "archivingTwo.h"
#include "other.h"

/*
    Main function takes the first argument (either -a, -u, -l, and -v) and then verifyies if the rest of the arguments are correct
    and match the given command, calling the corresponding function per the first argument's flag. The funcions called and their 
    corresponding flags are as follows:  
        -a archivename file1 file2 ... fileN: (archive)
        -u archivename:                       (unarchive) 
        -l archivename:                       (printArchiveDetails) Outputs details of archive to stdout.
        -v archivename file1 file2 ... fileN: (verifyArhive) Outputs integrity of archive to stdout.
*/

int main( int argc, char *argv[] )  {
    //Variables here:
    int numOfArgs = 0; //This is number of arguments.
    numOfArgs = argc - 1; //Calc. that

    char * archiveName; 

    // Print for peace of mind.
    printf("\nThe number of args is: %d\n", numOfArgs);

    //Check for at least two arguments.
    if (numOfArgs < 2){
        fprintf(stderr, "There were not enough arguments. ");
        exit(-1);
    }
    else if (strcmp(argv[1], "-a") == 0){
        //Check for atlest three args (not including exe)
        if (numOfArgs < 3){
            fprintf(stderr, "There were an incorrect number of args. ");
            exit(-1);  
        }

        //Create an archive.
        archiveName = strdup(argv[2]);

        //Check if there are multiple flags
        if (checkIfFlag(archiveName) == -1){
            exit(-1);  
        }

        printf("You supplied the archive name of: %s\n", archiveName);
        int numOfFiles; //The number of files.
        numOfFiles = numOfArgs - 2; //Calc. that
        printf("You supplied %d file names.\n", numOfFiles);

        //Dynamically allocate for the array of char pointers, one for each string
        char ** fileNames = malloc(numOfFiles * sizeof(char *));

        //Allocate space for each string
        int i; //Counting int
        for (i = 0; i < numOfFiles; ++i) {
            fileNames[i] = (char *)malloc(strlen(argv[i+3])+1);
            //Check if fileName is too long.
            if (strlen(argv[i+3]) >= sizeFileName){
                fprintf(stderr, "The file name would cause an overflow. ");
                exit(-1);              
            }
            strcpy(fileNames[i], argv[i+3]);
        }

        //Print out the fileNames
        int x; //Counting int
        for (x = 0; x < numOfFiles; ++x) {
            printf("%d: The file name: %s\n", x + 1, fileNames[x]);
        }
        
        archive(fileNames, numOfFiles, archiveName);

        //Free the memory of the dynamically allocated list here.
        int y;
        for (y = 0; y < numOfFiles; ++y){
            free(fileNames[y]);
        }
        free(fileNames);
    }
    else if (strcmp(argv[1], "-u") == 0){
        //Check if there are more than three args
        if (numOfArgs != 2){
            fprintf(stderr, "There were an incorrect number of args. ");
            exit(-1);
        }

        //Unpack an archive.
        archiveName = strdup(argv[2]);

        //Check if there are multiple flags
        if (checkIfFlag(archiveName) == -1){
            exit(-1);  
        }
        
        printf("You supplied the archive name of: %s\n", archiveName);

        unarchive(archiveName);
        
    }
    else if (strcmp(argv[1], "-l") == 0){
        //Check if there are more than three args
        if (numOfArgs != 2){
            fprintf(stderr, "There were an incorrect number of args. ");
            exit(-1);
        }

        //Prints an archive size.
        archiveName = strdup(argv[2]);

        //Check if there are multiple flags
        if (checkIfFlag(archiveName) == -1){
            exit(-1);  
        }

        printf("You supplied the archive name of: %s\n", archiveName);

        //printArchiveDetails(* archiveName);
        
    }
    else if (strcmp(argv[1], "-v") == 0){
        //Check for atlest three args (not including exe)
        if (numOfArgs < 3){
            fprintf(stderr, "There were an incorrect number of args. ");
            exit(-1);  
        }

        //Checks an archive.
        archiveName = strdup(argv[2]);

        //Check if there are multiple flags
        if (checkIfFlag(archiveName) == -1){
            exit(-1);  
        }

        printf("You supplied the archive name of: %s\n", archiveName);
        int numOfFiles; //The number of files.
        numOfFiles = numOfArgs - 2; //Calc. that
        printf("You supplied %d file names.\n", numOfFiles);

        //Dynamically allocate for the array of char pointers, one for each string
        char ** fileNames = malloc(numOfFiles * sizeof(char *));

        //Allocate space for each string
        int i; //Counting int
        for (i = 0; i < numOfFiles; ++i) {
            fileNames[i] = (char *)malloc(strlen(argv[i+3])+1);
            //Check if fileName is too long.
            if (strlen(argv[i+3]) >= sizeFileName){
                fprintf(stderr, "The file name would cause an overflow. ");
                exit(-1);              
            }
            strcpy(fileNames[i], argv[i+3]);
        }

        //Print out the fileNames
        int x; //Counting int
        for (x = 0; x < numOfFiles; ++x) {
            printf("%d: The file name: %s\n", x + 1, fileNames[x]);
        }

        //verifyArchive(**fileNames, numOfFiles, * archiveName);

        //Free the memory of the dynamically allocated list here.
        int y;
        for (y = 0; y < numOfFiles; ++y){
            free(fileNames[y]);
        }
        free(fileNames);
        
    }
    else{
        fprintf(stderr, "Unknown first argument supplied. ");
        exit(-1);
    }

   return 1;
} //End main
