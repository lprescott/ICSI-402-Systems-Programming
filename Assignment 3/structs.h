#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct termList{
	char * term;
	struct fileCountList * head;
	struct termList * next;
} termList;

typedef struct fileCountList{
	char * file
	struct fileCountList * next;
	struct termList * next;
} fileCountList;

#endif