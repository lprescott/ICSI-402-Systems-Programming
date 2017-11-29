#include <unistd.h>


void printDirectory(char *directory, size_t size){
	char directory[1024]
	if(getcwd(cwd, sizeof(cwd)) !=NULL)
		fprintf(stdout, " The Current Working directory is: %s\n", cwd);
	else
		 perror("Could not get current working directory")
		return 0;
}