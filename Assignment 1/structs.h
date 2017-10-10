#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct logline{
	char level[20];
	char timestamp[20];
	char message[100];
} logline_t;

typedef struct loglist {
	logline_t line;
	struct loglist *next;
} loglist_t;

/*
	Because of the typedefs, refer to these structure types as (for example) struct loglist or just loglist_t.
	I.E. struct loglist == loglist_t 
*/

#endif