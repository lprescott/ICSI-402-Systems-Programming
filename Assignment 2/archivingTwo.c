//Project: 	Prog1
//Names:   	Luke Prescott, Rob Rose, Tommy Li (lprescott@albany.edu, rwrose@albany.edu, tli3@albany.edu)
//Roles:   	Leader, Monitor, Recorder Respectively
//Date:    	10/19/2017
//Course:  	ICSI 402
//Desc:    	A function to handle the -l flag and a function to handle the - v flag.
//Input:
//Output:
//Assumption:

#include <stdio.h>

#include "archivingTwo.h"
#include "other.h"
#include "constants.h"

// function to handle -l flag
/*
  This function takes the archiveName, and opens the archive. If the archive exists, this will
  print the total size of the archive file, the names of all the individual files in the archive,
  and their respectie sizes.
*/
void printArchiveDetails(char* archiveName) {

}

///function to handle -v flag
/*
  Takes the archiveName, and checks to see if all the fileNames are contained within the archive.
  If the archive correctly contains all the files, then "Archive verified" is printed to the console.
  If the archive is missing data, then the program will print "Archive is missing X bytes" to the console.
  If the archive's data is incorrect, then the program will print "Archive is corrupted."
*/
void verifyArchive(char ** fileNames, int numFiles, char * archiveName) {

}
