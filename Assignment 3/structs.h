#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct termList{
	char * fileName;
	char * term;
	int count;
	struct termList * next;
} termList;

#endif