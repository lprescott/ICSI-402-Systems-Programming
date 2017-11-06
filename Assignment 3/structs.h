typedef struct fileCountList {
	char * fileName;
	int count;
	struct fileCountList * next;
} fileCountList;

typedef struct termList {
	char * term;
	fileCountList * firstFile;
	struct termList * next;
} termList; 