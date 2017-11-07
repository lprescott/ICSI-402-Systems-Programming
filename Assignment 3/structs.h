typedef struct termList{
	char * fileName;
	char * term;
	int count;
	struct termList * next;
} termList;