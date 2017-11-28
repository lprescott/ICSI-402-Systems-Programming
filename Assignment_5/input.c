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
    command = strtok(commandline, " ");

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
char ** createArgList(char * command, char * commandline){

} //End char ** createArgList(char * commandline)

/*

*/
void executeFile(char * command, char * commandline){
    //Variables
    pid_t  pid;
    pid_t c;
    int cstatus;

    //The string list to hold all arguments including program name
    char ** argList;
    argList = createArgList(command, commandline);

    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "ERROR: fork failed.\nExiting...\n");
        exit(-1);
    }
    if (pid == 0) {
        //Child process

        //Child details
        printf("Child - PID: %d and PPID: %d.\n", getpid(), getppid());

        //Call list program
        execvp(argList[0], argList);

        //If the child process reaches this point, execvp failed
        fprintf(stderr, "Child process could not execute execvp.\n");
        exit(-1);

    }
    else {
        //Parent process
		if (pid == (pid_t)(-1)) {
			fprintf(stderr, "ERROR: fork failed\n exiting...\n");
		    exit(-1);
        }

        //Wait for the child process to finish
        c = wait(&cstatus);

        //Parent details
        printf("Parent - PID: %d and PPID: %d.\n", getpid(), pid);
    }
} //End void executeFile(char * command, char * commandline)