//Project: 	Prog1
//Names:   	Luke Prescott, Rob Rose, Tommy Li (lprescott@albany.edu, rwrose@albany.edu, tli3@albany.edu)
//Roles:   	Leader, Monitor, Recorder Respectively
//Date:    	10/19/2017
//Course:  	ICSI 402
//Desc: contains the two functions, archive which creates an archive file from a set of individual files
//         unarchive function unpacks an archive file and create
        
//Input:   	
//Output:  	
//Assumption:	



#include <stdio.h>

#include "archiving.h"
#include "constants.h"
#include "other.h"

//archive function

void archive(char** filenames, int numFiles, char* archivename) {

	// concatenate ".bin" to a temp archiveName string.
	//opens a new bin file with new string for writing
	//print #of files to bin
	/* loop for numFiles through string array
		a)open file
	    b) get, store, print size of fileName
		c) get, store, print the fileName
		d) get, store, print size of contents( use fileSize() function here)
		e) get, store , print the contents
		f) close file
    */
	//close bin file



       
}

//unarchive function
void unarchive(char* archivefile) {
        
}
