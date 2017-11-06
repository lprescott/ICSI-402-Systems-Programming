#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "other.h"

//A third source file must contain only the function that browses through the files.
char ** browse(char * directoryPath){
	
	DIR * d = opendir(directoryPath);
	struct dirent * dir;
	
	if (d) {
		while ((dir = readdir(d)) != NULL) {
			printf("%s : ", dir->d_name);
			if (isFile(dir->d_name)) {
				printf("Is a file!\n");
			} else if(isDir(dir->d_name)) {
				printf("Is a Directory!\n");
				if ((strcmp(dir->d_name, ".") != 0) && (strcmp(dir->d_name, "..") != 0)) {
					browse(dir->d_name);
				}
			}
		}
		closedir(d);
	}
}