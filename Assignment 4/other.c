//included libraries
#include <unistd.h>

int fileExistsAndReadable(char * filename){
	if(access(filename, F_OK|R_OK) != -1) return 1;
	else return 0;
}
