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

/*
main function, takes parameters of for the number of arguments
*/
int main( int argc, char *argv[] )  {
	
// if the number of command line arguments is equal to 1, prints the arguments that are supplied
   if( argc == 2 ) {
      printf("The argument supplied is %s\n", argv[1]);
   }
   
   // if the number of command line arguments is greater than 1, prints to many arguments are supplied
   else if( argc > 2 ) {
      printf("Too many arguments supplied.\n");
   }
   // if the no arguments are supplied, it will print out that is expects an argument.
   else {
      printf("One argument expected.\n");
   }
}