char * getLine(FILE * stream);

int fileExists(char * filename);
int fileReadable(char * filename);

void parseCommandLine(int isFile, char * commandline);

char ** createArgList(int numArgs, char * commandline);
void executeFile(int numArgs, char ** commandline);