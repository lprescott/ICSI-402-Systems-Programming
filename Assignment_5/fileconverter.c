#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include "fileconverterFunctions.h"


int main( int argc, char *argv[] )  {
	
	printf("%d\n", argc);

	//NON INPUT REDIRECTION CASES
	//Case 1: flag infile outfile
	if ( argc == 4 ) {
		//Case 1 a) flag is -t
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
	else if ( argc == 3 ) {
		
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
	
	/*INPUT REDIRECTION CASES
	
	else if ( argc == 5 ) {
		
	}
    
	*/
	
    //Exit with 0, program was succesfully completed
	exit(0);
}