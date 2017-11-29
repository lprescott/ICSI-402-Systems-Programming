#include <stdlib.h>
#include <stdio.h>

/*
	The function takes no parameters, and returns nothings. printDirectory calls getcwd()
	and prints its return value to stdin.
*/
void printCWDirectory(void){
	//the directory string holds the return value
	char directory[255];
	if(getcwd(directory, sizeof(directory)) != NULL){
		printf("%s\n", directory);
	}
	else{
		//return is NULL, so exit with err.
		fprintf(stderr, "Could not get current working directory.\n");
	}
} //End void printDirectory()

/*

*/
void changeCWDirectory(char * pathname){
	int x = 0;
	x = chdir(pathname);

	if(x == -1){
		//return is -1, so exit with err.
		fprintf(stderr, "Could not change current working directory.\n");
	}
}//End void changeCWDirectory(char * pathname);