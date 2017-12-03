//Project: 	Prog5
//Names:   	Luke Prescott, Rob Rose, Tommy Li (lprescott@albany.edu, rwrose@albany.edu, tli3@albany.edu)
//			(001252879, 001247373, 001209184)
//Roles:   	Leader, Monitor, Recorder Respectively
//Date:    	11/28/2017
//Course:  	ICSI 402

/*Desc: this file contains the necessary functions associated with the fileconverter command.
the role of the fileconverter command is for converting a text file into a binary file and vice versa.
The program will support the following commands that are supplied by the user

(1) fileconverter flag infile outfile: the names of the input and output files are represented
by the parameters infile and outfile. For the flag parameter, either -t or -b can be used
, the -t flag represents a text file as the inputfile, and the output file is suppose to be a representation
of the lines of the text file, contained in binary format. The -b flag represents a binary file as the inputfile
file, and the output file is suppose to a representation of the lines in the binary file in text format.

(2) fileconverter -s infile: the parameter infile is the representation of the name of the binary input file, was 
created previously from a text file. With this function, the program should be able to process the input file, 
and print information to stdout. The information that is printed include the full name of the student, that has the
greatest name length that is combined. It should also be able to print the full name of the student has the smallest name length
combined. Also the based on the information in the file, the highest id number value, the lowest id number value, and the value
of the highest and lowest GPAs are also printed out. The output of this program should be printed straight to stdout, it shouldn't
produce an output file.

 /*
 Output: the output depends on the arguments being supplied by the user when using the fileconverter command. 
*/

//standard c libraries
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>

//included external header files containing prototypes
#include "fileconverterFunctions.h"


int main( int argc, char *argv[] )  {
	
	printf("%d\n", argc);

	//NON INPUT REDIRECTION CASES
	//Case 1: fileconverter flag infile outfile
	
	//if number of arguments is equal to 4 print case
	if ( argc == 4 ) {
		printf("CASE 1\n");
		//Case 1 a) flag is -t
		// if the second argument supplied is equal to -t, check if the file supplied is a text file
		if ( strcmp(argv[1], "-t") == 0 ) {
			
			//Check if the second argument is a readable file
			/*if ( !isReadableFile( argv[2] ) ) {
				fprintf(stderr, "ERROR: first file given isn't readable");
				exit(-1);
			}*/
			
			//Check if the third argument is a binary file
			/*if ( !isBinaryFile ( argv[3] ) ) {
				fprintf(stderr, "ERROR: second file given isn't binary");
				exit(-1);
			}*/
			
			//Call file converter for binary
			//convertToBinary( argv[2], argb[3] );
			
		}
		//Case 1 b) flag is -b
		// if the second argument supplied is equal to -b, check if the file supplied is a binary file
		if ( strcmp(argv[1], "-b") == 0 ) {
			
			//Check if the second argument is a binary file
			/*if ( !isBinaryFile( argv[2] ) ) {
				fprintf(stderr, "ERROR: first file given isn't binary");
				exit(-1);
			}*/
			
			//Check if the third argument is a readable file
			/*if ( !isReadableFile ( argv[3] ) ) {
				fprintf(stderr, "ERROR: second file given isn't readable");
				exit(-1);
			}*/
			
			//Call file converter for binary
			//convertToReadable( argv[2], argb[3] );
			
		}
		
	} 
	//Case 2: flag is -s
	//if the number of arguments supplied is equal to 3, print case 2
	else if ( argc == 3 ) {
		printf("CASE 2\n");
		// if the 2nd argument supplied is equal to -s, check if supplied file is binary
		if ( strcmp(argv[1], "-s") == 0 ) {
			
			//Check if the second argument is a binary file
			/*if ( !isBinaryFile( argv[2] ) ) {
				fprintf(stderr, "ERROR: first file given isn't binary");
				exit(-1);
			}*/
			
			//call printDetails()
			//printDetails( argv[2] );
			
		}
		
	}
	
	//INPUT REDIRECTION CASES
	
	//Case 3: flag is -s AND with > file.txt
	else if ( argc == 5 ) {
		printf("CASE 3\n");
		if ( strcmp(argv[1], "-s") == 0 ) {
			
			//Check if the second argument is a binary file
			/*if ( !isBinaryFile( argv[2] ) ) {
				fprintf(stderr, "ERROR: first file given isn't binary");
				exit(-1);
			}*/
		        // if the 4th argument supplied contains a >, output will be redirected
			if ( strcmp(argv[3], ">") == 0) {
				
				//saved is a stored file descriptor for stdout
				//tempOut is a stored file descriptor for the supplied file
				int saved; int tempOut; 

				//Open (create) the supplied file
				tempOut = open(argv[4], O_WRONLY | O_APPEND | O_CREAT, 0644);
				
				if (tempOut < 0) {
					fprintf(stderr, "ERROR: unable to open suppled file.\n");
					exit(-1);
				}
				
				//store the file descriptor for stdout
				saved = dup(1);

				//redirect output
				dup2(tempOut, 1);
				
				//call printDetails()
				//printDetails( argv[2] );
			   
				//return output to normal
				dup2(saved, 1);
				
			}
			
		}
		
	}
	
    //Exit with 0, program was succesfully completed
	exit(0);
}
