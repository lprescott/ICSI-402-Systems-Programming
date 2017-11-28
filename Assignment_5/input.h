char * getLine(FILE * stream);

int fileExists(char * filename);
int fileReadable(char * filename);

void callCommands(int file, char * commandline);

char ** createArgList(char * command, char * commandline);
void executeFile(char * command, char * commandline);