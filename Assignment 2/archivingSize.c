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

*/
long fileSize(FILE * file){
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