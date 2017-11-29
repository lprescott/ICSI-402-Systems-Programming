//Project: 	Prog5
//Names:   	Luke Prescott, Rob Rose, Tommy Li (lprescott@albany.edu, rwrose@albany.edu, tli3@albany.edu)
//			(001252879, 001247373, 001209184)
//Roles:   	Leader, Monitor, Recorder Respectively
//Date:    	11/28/2017
//Course:  	ICSI 402

/*Desc: the role of the list command is that prints to the standard output, the information
about the files that are contained in a directory. List is a separate program, so it can be called
manually, by executing its own executable file or from simpleshell.

the program supports the following usage with the following arguments depending on the supplied arguments

(1): list pathname
 when the pathname is a an absolute or relative pathname to a directory. this command
 will print all of the non hidden file names that are contained in a specified directory,
 with one file per a line. Any file names that don't start with a dot are considered to
 be hidden files.

(2): list -i pathname
The -i flag is an indication that any extra information needs to be printed.
The informationthat is printed from this command include the name of the file with
one file per a line. The size of the file stated in bytes, the permission associated
it printed in octal format, and the inode number that is stated as a decimal integer.

(3): list -h pathname
the -h flag is an indication that only hidden files names in a specified directory 
should be printed.

(4): list, list -i, list -h
 any of these commands function the same as the command above, but they are executed
 in the current working directory instead a path that is specified.

/*
Output: the output depends on the arguments being supplied by the user when using the list
command.
*/

//standard c libraries
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
  This function finds file size by seeking all the way to the end on the file, then telling the long
  position the position of the end character. This position is the size of the file in bytes. It only takes,
  one argument, which is the FILE type needed to point to.
  
  Trouble with makefile, put here until we can resolve it.
*/
long fileSize(FILE * file) {
    //Position: the variable to be returned, and the position of the end character.S
    long position;

	// if it is null, and error is printed and terminates
    if (file == NULL){
        fprintf(stderr, "Error opening file.\n");
        return(-1);
    }

    fseek(file, 0, SEEK_END);// sets the file position of the stream to the given offset

    position = ftell(file);// ftell returns the current file postion of the given stream, and that is the value of position.

    rewind(file);// returns to the beginning of the file

    return position;// returns the position of the file offset
}

/*
main function, takes parameters of for the number of arguments
*/
int main( int argc, char *argv[] )  {

	FILE * inputFile; //A file that is used to find the size of each file
	char * pathName; //THe path name for the directory directory
	char * fileName; //THe file name we use for each file to be printed
	char * filePath; //The path to the file, used for -i flag
	DIR * directory; //Directory pointer
	struct dirent * ent; //File info from the directory pointer
	int i; //for for loops
	int inode, fd; //The innode and file descriptor, respectively
	struct stat file_stat; //The stat structure to hold onto the stat of the file
	mode_t bits; //The permission bits for each file
	
	printf("\nIn List\n\n");
	printf("\tArguments:\n");
	for (i = 0; i < argc; i++) {
		printf("\t\tArg %d : \"%s\"\n", i, argv[i]); fflush(stdout);
	}
	printf("\n");

	// if the number of command line arguments is equal to 1, prints the arguments that are supplied
	//First Case : only the pathname is given
	if( argc == 2 ) {
	  
		//Duplicates the path to Pathname
		pathName = strdup(argv[1]);
		
		
		printf("\tThe Pathname \"%s\"\n", pathName); 
		
		//Opens directory, and checks if valid
		directory = opendir(pathName);
		if (directory == NULL) {
			fprintf(stderr, "\tERROR in list: Directory can't be opened.\n Exiting...\n");
			exit(-1);
		}
		
		//While each dirent struct read from directory != null, it prints the name
		while ((ent = readdir(directory)) != NULL) {
			fileName = strdup(ent->d_name);
			//if the name is == to "." and "..", do not print because they aren't files
			if ((strcmp(".", fileName) != 0) && (strcmp("..", fileName) != 0)) {
				printf("\t%s\n", fileName);
			}
		}
		
		//Close
		closedir(directory);
		
	}
   
   else if( argc = 3 ) {
      //Case 2: flag is -i
	  if (strcmp(argv[1], "-i") == 0) {
		//Duplicate Pathname
		pathName = strdup(argv[2]);
		
		
		printf("\tThe Pathname \"%s\"\n", pathName); 
		
		//Open Directory and checks if it can be read
		directory = opendir(pathName);
		if (directory == NULL) {
			fprintf(stderr, "\tERROR in list: Directory can't be opened.\n Exiting...\n");
			exit(-1);
		}
		
		//While each dirent struct read from directory != null, it prints the name
		while ((ent = readdir(directory)) != NULL) {
			
			//Duplicates ent->name into FileName
			fileName = strdup(ent->d_name);
			
			//The next four lines create the file path so that inputFile can be opened
			filePath = strdup(pathName);
			strcat(filePath, "/");
			strcat(filePath, fileName);
			printf("\t\tfilePath : \"%s\"\n", filePath);
			
			
			//if the name is == to "." and "..", do not print because they aren't files
			if ((strcmp(".", fileName) != 0) && (strcmp("..", fileName) != 0)) {
				
				inputFile = fopen(filePath, "r");
				if (inputFile == NULL) {
					fprintf(stderr, "\tERROR in line: Trouble opening input file.\n");
				}
				
				//This is the file descriptor being opened
				fd = open(filePath, O_RDONLY);
				int ret = fstat(fd, &file_stat);
				
				if (ret < 0) {
					//error
					fprintf(stderr, "\tERROR in list: trouble opening stat\n");
					exit(-1);
				}
				
				inode = file_stat.st_ino;
				bits = file_stat.st_mode;
				
				printf("\t%s : %ld : %04o : %d\n", fileName, fileSize(inputFile), bits, inode);
			}
			
			fclose(inputFile);
			
		}
		
		closedir(directory);
	  }
	  //Case 3: flag is -h
	  else if (strcmp(argv[1], "-h") == 0) {
		//Duplicates the path name
		pathName = strdup(argv[2]);
	  
		printf("\tThe Pathname \"%s\"\n", pathName); 
		
		//Opens Directory and checks to see if the directory is null
		directory = opendir(pathName);
		if (directory == NULL) {
			fprintf(stderr, "\tERROR in list: Directory can't be opened.\n Exiting...\n");
			exit(-1);
		}
		
		//While ent != null get the name and then print
		while ((ent = readdir(directory)) != NULL) {
			fileName = strdup(ent->d_name);
			//If the fileName == . or .., do not print
			if ((strcmp(".", fileName) != 0) && (strcmp("..", fileName) != 0)) {
				//print only if the first character of filename is a .
				if (fileName[0] == '.') {
					printf("\t%s\n", fileName);
				}
			}
		}
		
		closedir(directory);
	  
	  }
	  
	  
   }
   // if the no arguments are supplied, it will print out that is expects an argument.
   else {
      printf("\t\tOne argument expected.\n");
   }

   printf("\n");
}