#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/*	
	A Naive Shell that prompts the user for a command, then calls 
	a child process to print out the command, and waits for the child to end.
*/

void main() {
	
	pid_t child;
	pid_t c;
	int cstatus;
	
	if ((child = fork()) == 0) {
		//Child
		printf("Correct Output: \"%s\"\n", inputBuffer);
		exit(1);
		
	}
	else {
		//parent
		if (child == (pid_t)(-1)) {
			fprintf(stderr, "ERROR: fork failed\n exiting...\n");
			exit(-1);
		}
		
		char inputBuffer[1024];
		c = wait(cstatus);
		
		printf("Shell~ ");
		scanf("%[^\n]%*c", inputBuffer);
	}
		

}