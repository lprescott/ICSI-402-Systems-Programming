/**
 * Project: Prog2
 * Names:   	Luke Prescott, Rob Rose, Tommy Li (lprescott@albany.edu, rwrose@albany.edu, tli3@albany.edu)
 * Roles:   	Leader, Monitor, Recorder Respectively
 * Date:    	10/19/2017
 * Course:  	ICSI 402
 * Desc:         This program is a modified .tar archiving tool, used to create and unpack .tar file.
 * Input:        A command line argument with the commands -a, -u, -l, -v.
 *              -a archivename file1 file2 ... fileN:  creates an archive with the specified name and files given after the command.
 *	            -u archivename:                        Unpacks an archive with the given name.
 *	            -l archivename:                        Print to stdout the names and total size of the archive and each file.
 *	            -v archivename file1 file2 ... fileN:  determines weather or not the specified archive is damaged
 * output:       Depends on the command
 * assumption:   The user will give one and only one command while calling archiver 
**/

//Included libraries:
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>

//Included files:
#include "constants.h"
#include "archiving.h"
#include "archivingSize.h"
#include "archivingTwo.h"
#include "other.h"


int main( int argc, char *argv[] )  {

   if( argc == 2 ) {
      printf("The argument supplied is %s\n", argv[1]);
   }
   else if( argc > 2 ) {
      printf("Too many arguments supplied.\n");
   }
   else {
      printf("One argument expected.\n");
   }

   return 1;
}