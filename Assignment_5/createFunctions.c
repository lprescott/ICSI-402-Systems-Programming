#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

/*

*/
void createFile(char * fileName) {
	
	int fd; //The file descriptor
	
	fd = open(fileName, O_RDWR | O_APPEND | O_CREAT, 0640);
	
	printf("createFile called\n");
	
}

/*

*/
void createDirectory(char * directoryName) {
	
	struct stat st = {0};
	
	if (stat(directoryName, &st) == -1) {
		mkdir(directoryName, 0750);
	}
	
}

/*

*/
void makeHardLink(char * oldName, char * linkName) {
	
}

/*

*/
void makeSoftLink(char * oldName, char * linkName) {
	
}