//standard c libraries
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
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

void printNames(char * path){

    char * fileName; //THe file name we use for each file to be printed
    DIR * directory; //Directory pointer
    struct dirent * ent; //File info from the directory pointer

    //Opens directory, and checks if valid
    directory = opendir(path);
    if (directory == NULL) {
        fprintf(stderr, "ERROR in listFunctions.c: Directory can't be opened.\nExiting...\n");
        exit(-1);
    }
    
    //While each dirent struct read from directory != null, it prints the name
    while ((ent = readdir(directory)) != NULL) {
        fileName = strdup(ent->d_name);
        //if the name is == to "." and "..", do not print because they are hidden
        if (fileName[0] != '.') {
            printf("%s\n", fileName);
        }
        free(fileName);
    }
    
    //Close
    closedir(directory);
}

void printDetails(char * path){

    char * fileName; //THe file name we use for each file to be printed
    DIR * directory; //Directory pointer
    struct dirent * ent; //File info from the directory pointer
    char filePath[255]; //The path to the file, used for -i flag
    FILE * inputFile; //A file that is used to find the size of each file
    int inode, fd; //The innode and file descriptor, respectively
	struct stat file_stat; //The stat structure to hold onto the stat of the file
	mode_t bits; //The permission bits for each file

    //Opens directory, and checks if valid
    directory = opendir(path);
    if (directory == NULL) {
        fprintf(stderr, "ERROR in listFunctions.c: Directory can't be opened.\nExiting...\n");
        exit(-1);
    }
    
    //While each dirent struct read from directory != null, it prints the name
    while ((ent = readdir(directory)) != NULL) {

        //Duplicates ent->name into FileName
        fileName = strdup(ent->d_name);
        
        //The next four lines create the file path so that inputFile can be opened
        strcpy(filePath, path);

        //Checks if the supplied path already ends in a /
        //If not, adds one
        char * ptr;
        ptr = strstr(filePath, "\0");
        printf("*%s*\n", ptr);
        if(ptr[strlen(ptr) - 1] != '/'){
            strcat(filePath, "/");
        }
        strcat(filePath, fileName);

        
        printf("\t\tfilePath : \"%s\"\n", filePath);
        
        /*
        //if the name is == to "." and "..", do not print because they are hidden
        if (fileName[0] != '.') {
            inputFile = fopen(filePath, "r");
            if (inputFile == NULL) {
                fprintf(stderr, "\tERROR in line: Trouble opening input file.\n");
                exit(-1);
            }
            printf("%s\n", fileName);
            fclose(inputFile);
        }
        
        free(filePath);
        */
        free(fileName);
        
    }
    
    //Close
    closedir(directory);

    /*
    //Opens directory, and checks if valid
    directory = opendir(path);
    if (directory == NULL) {
        fprintf(stderr, "ERROR in listFunctions.c: Directory can't be opened.\nExiting...\n");
        exit(-1);
    }
    
    //While each dirent struct read from directory != null, it prints the name
    while ((ent = readdir(directory)) != NULL) {

        //Duplicates ent->name into FileName
        fileName = strdup(ent->d_name);
        
        //The next four lines create the file path so that inputFile can be opened
        filePath = strdup(path);
        strcat(filePath, "/");
        strcat(filePath, fileName);
        printf("\t\tfilePath : \"%s\"\n", filePath);
        

        //if the name is == to "." and "..", do not print because they are hidden
        if (fileName[0] != '.') {

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
            
            //printf("\t%s : %ld : %o : %d\n", fileName, fileSize(inputFile), bits, inode);
            printf("%s", fileName);
            fclose(inputFile);
        }

        free(fileName);
        free(filePath);
    }
    
    //Close
    closedir(directory);
    */
}

void printHidden(char * path){
    
    char * fileName; //THe file name we use for each file to be printed
    DIR * directory; //Directory pointer
    struct dirent * ent; //File info from the directory pointer

    //Opens directory, and checks if valid
    directory = opendir(path);
    if (directory == NULL) {
        fprintf(stderr, "ERROR in list.c: Directory can't be opened.\nExiting...\n");
        exit(-1);
    }
    
    //While each dirent struct read from directory != null, it prints the name
    while ((ent = readdir(directory)) != NULL) {
        fileName = strdup(ent->d_name);
        //if the name is == to "." and "..", do not print because they are hidden
        if (fileName[0] == '.') {
            printf("%s\n", fileName);
        }
        free(fileName);
    }
    
    //Close
    closedir(directory);
}