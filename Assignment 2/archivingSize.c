//Project: 	Prog1
//Names:   	Luke Prescott, Rob Rose, Tommy Li (lprescott@albany.edu, rwrose@albany.edu, tli3@albany.edu)
//Roles:   	Leader, Monitor, Recorder Respectively
//Date:    	10/19/2017
//Course:  	ICSI 402
//Desc:    	this function computes the size of the a file

//standard c libraries
#include <stdio.h>
#include <stdlib.h>

// included external header files
#include "constants.h"
#include "archivingSize.h"

/*
  This function finds file size by seeking all the way to the end on the file, then telling the long
  position the position of the end character. This position is the size of the file in bytes. It only takes,
  one argument, which is the FILE type needed to point to.
*/
long fileSize(FILE * file){
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
