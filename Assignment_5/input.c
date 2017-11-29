#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "input.h"

/*
    This function reads one line from the specified file and returns the result as a null terminated string.
*/
char * getLine(FILE * stream){
    
    //lineSize is the maximum size of a line, and line is a pointer to the start of the read line
    const size_t lineSize = 1024;
    char * line = malloc(lineSize);
    //newLine is a char * to the line without the '\n' character 
    char * newLine;

    //Gets one line from stream, returning NULL if empty
    if (fgets(line, lineSize, stream)!= NULL){

        //Check if it ends with a newline, then replaces it with a terminator
        if(line[strlen(line)-1] == '\n'){
            line[strlen(line)-1] = '\0';

            //Free and return
            newLine = strdup(line);
            free(line);
            return newLine;
        }
        //Otherwise, just leave it be
        else{
            //Free and return
            newLine = strdup(line);
            free(line);
            return newLine;
        }
    }
    //fgets returned NULL
    else{
        //Free and return
        free(line);
        return NULL;
    }

} //End char* getLine(FILE * stream)

//Helper functions below this point

/*
	This function returns a 1 if the supplied file name exists  by using the access function. 
	If the supplied file name does not exist, the function returns 0.
*/
int fileExists(char * filename){
	//F_OK is used for checking if the file is readable
	if(access(filename, F_OK) != -1) return 1;
	else return 0;
} //End int fileExists(char * filename)

/*
	This function returns a 1 if the supplied file name is readable by using the access function. 
	If the supplied file name is not readable, the function returns 0.
*/
int fileReadable(char * filename){
	//R_OK is used for checking if the file is readable
	if(access(filename, R_OK) != -1) return 1;
	else return 0;
} //End int fileReadable(char * filename)

/*

*/
void parseCommandLine(int isFile, char * commandline) {
    char ** arguments; //A list of string arguments passed to the shell

    //printf("commandline: \"%s\".\n", commandline);

    if ((commandline[0] == '\0') || (commandline[0] == ' ')){   

        if(isFile == 0){
            //Print shell name for next command
            printf("simpleshell:~$ ");
        }
        return;
    }
    
    int i=0, numArgs=0;
    //For loop to determine number of arguments
    while (commandline[i] != '\0'){
        if (commandline[i] == ' '){
            numArgs++;    
        }
        i++;
    } 

    //Increment by one because of word after last space
    numArgs++;
    
    //The string list to hold all arguments including program name
    char ** argList;
    argList = createArgList(numArgs, commandline);

    //if command should quit simpleshell, then exit with (1)
    if(strcmp(argList[0], "quit") == 0){
        printf("goodbye\n");
        exit(1);
    }
    else if(strcmp(argList[0], "list") == 0){

        //Call executeChildProcess (which creates a child process)
        executeChildProcess(numArgs, argList);
    }
    else if(strcmp(argList[0], "create") == 0){
                
        //Call executeChildProcess (which creates a child process)
        executeChildProcess(numArgs, argList);
    }
    else if(strcmp(argList[0], "wd") == 0){
        
    }
    else if(strcmp(argList[0], "chwd") == 0){
        
    }
    else if(strcmp(argList[0], "fileconverter") == 0){
                
        //Call executeChildProcess (which creates a child process)
        executeChildProcess(numArgs, argList);
    }
    else{
        fprintf(stderr, "ERROR: command not found.\n");
    }

    if(isFile == 0){
        //Print shell name for next command
        printf("simpleshell:~$ ");
    }

    //Loop to free the mem of the list of args (and print)
    for(i = 0; i < numArgs; i++)
    {
        //(print) the free
        //printf("%d \"%s\"\n", i, argList[i]);
        free(argList[i]);
    } 

    //Free the list pointer
    free(argList);


} //End void parseCommandLine(int file, char * commandline)

/*

*/
char ** createArgList(int numArgs, char * commandline){

    const char s[2] = " ";
    char * token; int pos = 0;
    char ** argList = malloc((numArgs + 1) * sizeof(char *));
	
	token = strtok(commandline, s);
	
    while( token != NULL ) {

        argList[pos] = malloc(strlen(token) + 1 * sizeof(char));
        strcpy(argList[pos], token);

        pos ++;
        token = strtok(NULL, s);  
	}
    
    //End the argList with NULL
	argList[pos] = NULL;
    return argList;

} //End char ** createArgList(char * commandline)

/*

*/
void executeChildProcess(int numArgs, char ** argList){

    //Variables
    pid_t  pid;
    pid_t c;
    int cstatus;

    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "ERROR: fork failed.\nExiting...\n");
        exit(-1);
    }
    if (pid == 0) {
        //Child process

        //Child details
        printf("\tChild - PID: %d and PPID: %d.\n", getpid(), getppid());

        //Call program
        execvp(argList[0], argList);

        //If the child process reaches this point, execvp failed
        fprintf(stderr, "Child process could not execute execvp.\n");
        exit(-1);
    }
    else {
        //Wait for the child process to finish
        c = wait(&cstatus);

        //Parent details
        printf("\tParent - PID: %d and PPID: %d.\n", getpid(), pid);

        //Child status
        printf("\tParent - Child %ld exited with status: %d.\n", (long) c, cstatus);
    }
    
} //End void executeChildProcess(char * command, char * commandline)