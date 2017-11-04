#include <stdio.h>
#include <sys/stat.h>

int isFile(const char * path) {
	struct stat buf;
	stat(path, &buf);
	return S_ISREG(buf.st_mode);
}

int isDir(const char * path) {
	struct stat buf;
	stat(path, &buf);
	return S_ISDIR(buf.st_mode);
}

/*
void printContents(LIST);
*/