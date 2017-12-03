typedef struct studentRecord {
	unsigned char l1;
	unsigned char l2;
	char * firstName;
	char * lastName;
	int id;
	int GPA;
} studentRecord;

int isBinaryFile(char * testFile);
int isReadableFile(char * testFile);

void convertToReadable(char * inputFileName, char * outputFileName);
void convertToBinary(char * inputFileName, char * outputFileName);
void printDetails(char * inputFileName);