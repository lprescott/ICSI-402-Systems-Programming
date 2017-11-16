//included libraries
#include <unistd.h>

/*
	This function returns a 1 if the supplied file name exists  by using the access function. 
	If the supplied file name does not exist, the function returns 0.
*/
int fileExists(char * filename){
	//F_OK is used for checking if the file is readable
	if(access(filename, F_OK) != -1) return 1;
	else return 0;
}

/*
	This function returns a 1 if the supplied file name is readable by using the access function. 
	If the supplied file name is not readable, the function returns 0.
*/
int fileReadable(char * filename){
	//R_OK is used for checking if the file is readable
	if(access(filename, R_OK) != -1) return 1;
	else return 0;
}