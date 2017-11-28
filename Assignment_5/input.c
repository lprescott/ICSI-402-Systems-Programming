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
			printf("1. Line \"%s\"\n", line);
			
            newLine = strdup(line);
            free(line);
            return newLine;
        }
        //Otherwise, just leave it be
        else{
            //Free and return
			printf("2. Line \"%s\"\n", line);
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
void callCommands(int file, char * commandline) {
    char * command; //The first word in the commandline, the command.
    char ** arguments; //A list of string arguments passed to the shell

    if (commandline[0] == '\0'){   

        fprintf(stderr, "ERROR: Empty command.\n");

        if(file == 0){
            //Print shell name for next command
            printf("simpleshell:~$ ");
        }
        return;
    }
    
    //Determine command then check
    command = strdup(commandline);
    command = strtok(command, " ");

    //if command should quit simpleshell, then exit with (1)
    if(strcmp(command, "quit") == 0){
        printf("goodbye\n");
        exit(1);
    }
    else if(strcmp(command, "list") == 0){

        //Call executeFile (which creates a child process)
        executeFile(command, commandline);
    }
    else if(strcmp(command, "create") == 0){
                
        //Call executeFile (which creates a child process)
        executeFile(command, commandline);
    }
    else if(strcmp(command, "wd") == 0){
        
    }
    else if(strcmp(command, "chwd") == 0){
        
    }
    else if(strcmp(command, "fileconverter") == 0){
                
        //Call executeFile (which creates a child process)
        executeFile(command, commandline);
    }
    else{
        fprintf(stderr, "ERROR: Invalid command.\n");
    }

    if(file == 0){
        //Print shell name for next command
        printf("simpleshell:~$ ");
    }

} //End void callCommands(int file, char * commandline)

/*

*/
char ** createArgList(int numArgs, char * command, char * commandline){

    const char s[2] = " ";
    char * token; int pos = 0;
    char ** argList = malloc(numArgs * sizeof(char *));
   
    token = strtok(commandline, s);
   
    while( token != NULL ) {

        argList[pos] = malloc(strlen(token) + 1 * sizeof(char));
        strcpy(argList[pos], token);
   
        pos ++;
        token = strtok(NULL, s);  
    }
    
    return argList;

} //End char ** createArgList(char * commandline)

/*

*/
void executeFile(char * command, char * commandline){

    //Variables
    pid_t  pid;
    pid_t c;
    int cstatus;
    int numArgs = 0, i = 0;

    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "ERROR: fork failed.\nExiting...\n");
        exit(-1);
    }
    if (pid == 0) {
        //Child process

        //Child details
        printf("Child - PID: %d and PPID: %d.\n", getpid(), getppid());

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
        argList = createArgList(numArgs, command, commandline);

        //Call program
        execvp(argList[0], argList);

        //Loop to free the mem of the list of args (and print)
        int i = 0;
        for(i = 0; i < numArgs; i++)
        {
            //(print) the free
            printf("%d \"%s\"\n", i, argList[i]);
            free(argList[i]);
        } 

        //Free the list pointer
        free(argList);

        //If the child process reaches this point, execvp failed
        fprintf(stderr, "Child process could not execute execvp.\n");
        exit(-1);

    }
    else {
        //Wait for the child process to finish
        c = wait(&cstatus);

        //Parent details
        printf("Parent - PID: %d and PPID: %d.\n", getpid(), pid);

        //Child status
        printf("Parent - Child %ld exited with status: %d.\n", (long) c, cstatus);

    }
} //End void executeFile(char * command, char * commandline)

//Adds New Line character '\n' to the end of a file if it is not there.
void addNewLine(char * fileName) {
	
	FILE * newFile = fopen(fileName, "a+");
	char test;
	
	fseek(newFile, -1, SEEK_END);
	
	if ((test = fgetc(newFile)) != '\n') {
		printf("\t\tNo NewLine, %c\n", test);
		fseek(newFile, 0, SEEK_END);
		fputc('\n', newFile);
	}
	fclose(newFile);
	
}