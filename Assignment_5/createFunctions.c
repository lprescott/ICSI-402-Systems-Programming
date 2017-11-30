//Project: 	Prog5
//Names:   	Luke Prescott, Rob Rose, Tommy Li (lprescott@albany.edu, rwrose@albany.edu, tli3@albany.edu)
//			(001252879, 001247373, 001209184)
//Roles:   	Leader, Monitor, Recorder Respectively
//Date:    	11/28/2017
//Course:  	ICSI 402

/*Desc: this file contains the necessary functions associated with the create command.
The functions contained include createFile, createDirectory, createHardLink, createSoftLink

 /*
 Output: the output depends on the arguments being supplied by the user when using the create
 command.
*/


//standard c libraries
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

/*
	This function takes fileName and creates a file named fileName
*/
void createFile(char * fileName) {
	
	int fd; //The file descriptor
	
	//Opens a file that can be read, written too, and appended with permissions 0640
	fd = open(fileName, O_RDWR | O_APPEND | O_CREAT, 0640);
	
}

/*
	This function takes a directoryName and creates a directory named 
	directoryName
*/
void createDirectory(char * directoryName) {
	
	struct stat st = {0}; //Stat struct to test weather directoryName exists
	
	//If directoryName doesn't exist, create the directory
	if (stat(directoryName, &st) == -1) {
		//creates the directory directoryName
		mkdir(directoryName, 0750);
	} 
	else {
		printf("\tDirectory already exists\n");
		return;
	}
	
}

/*
	This function takes oldName and linkName and creates a hardLink from
	oldName to linkName
*/
void createHardLink(char * oldName, char * linkName) {
	
	//if link() returns -1, a link cannot be created, else link creates a hard link between oldName and linkName
	if (link(oldName, linkName) == -1) {
		fprintf(stderr, "\tERROR in create: hard link can't be created. %s\n\tExiting...\n", strerror(errno));
		exit(-1);
	}
	
}

/*
	This function takes oldName and linkName and creates a hardLink from
	oldName to linkName
*/
void createSoftLink(char * oldName, char * linkName) {
	
	//if link() returns -1, a link cannot be created. Else, the link creates a soft link between oldName and linkName
	if (symlink(oldName, linkName) == -1) {
		fprintf(stderr, "\tERROR in create: soft link can't be created. %s\n\tExiting...\n", strerror(errno));
		exit(-1);
	}
	
}