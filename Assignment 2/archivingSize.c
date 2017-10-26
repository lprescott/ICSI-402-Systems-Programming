//Project: 	Prog1
//Names:   	Luke Prescott, Rob Rose, Tommy Li (lprescott@albany.edu, rwrose@albany.edu, tli3@albany.edu)
//Roles:   	Leader, Monitor, Recorder Respectively
//Date:    	10/19/2017
//Course:  	ICSI 402
//Desc:    	this function computes the size of the a file

//standard c libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// included external header files
#include "constants.h"
#include "archivingSize.h"

/*
  This function finds file size by seeking all the way to the end on the file, then telling the long
  position the position of the end character. This position is the size of the file in bytes. It only takes,
  one argument, which is the file name.
*/
long fileSize(char * fileName)){
  struct stat buffer
  if (stat(file_name, &buffer) != 0)
  {
    fprintf(stderr, "Stat has failed in fileSize().");
    exit(-1);
  }
  return buffer.st_size;
}
