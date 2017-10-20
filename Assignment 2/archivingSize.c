//Project: 	Prog1
//Names:   	Luke Prescott, Rob Rose, Tommy Li (lprescott@albany.edu, rwrose@albany.edu, tli3@albany.edu)
//Roles:   	Leader, Monitor, Recorder Respectively
//Date:    	10/19/2017
//Course:  	ICSI 402
//Desc:    	this function computes the size of the a file
//Input:
//Output:
//Assumption:

#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "archivingSize.h"

/*
  This function finds file size by seeking all the way to the end on the file, then telling the long
  position the position of the end character. This position is the size of the file in bytes.
*/
long fileSize(FILE * file){
    //Position: the variable to be returned, and the position of the end character.S
    long position;

    if (file == NULL){
        fprintf(stderr, "Error opening file.\n");
        return(-1);
    }

    fseek(file, 0, SEEK_END);

    position = ftell(file);

    fclose(file);

    return position;
}
