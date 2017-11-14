//included libraries
#include <unistd.h>

/*
	This function returns a 1 if the supplied file name exists and is readable by using the access function. 
	If the supplied file name does not exist or is not readable, the function returns 0.
*/
int fileExistsAndReadable(char * filename){
	//F_OK|R_OK are used for checking if the file is existing (F_OK) and readable (R_OK)
	if(access(filename, F_OK|R_OK) != -1) return 1;
	else return 0;
}