//Project: 	Prog1
//Names:   	Luke Prescott, Rob Rose, Tommy Li (lprescott@albany.edu, rwrose@albany.edu, tli3@albany.edu)
//Roles:   	Leader, Monitor, Recorder Respectively
//Date:    	10/3/2017
//Course:  	ICSI 402
//Desc:    	This program takes directory full of log files then concatonates them into
//         	a single log file, where the order is based on the time of each log.
//Input:   	The program can take a command line argument specifying the path where the program will execute
//	   	Otherwise, it will execute in the current directory
//Output:  	A .log file and standard output of the printed merge list
//Assumption:	The possible command line argument is assumed to be a unix path to a directory in unix.

// headers of standard c library
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//include external header files.
#include "structs.h"
#include "headersOther.h"

/*
int looksCorrect(char * line){
    if(){
        return 1;
    }
    else{
      else return 0;
    }
}
*/

//checks to see if a log entry contains two commas
int containsTwoPlusCommas(char * line){
    int count = 0;// the initial count is set to zero
    int x = 0;
	//while line hasnt ended
    while(line[x] != EOF){
	  //if it contains a comma
      if (line[x] == ','){
		  //increment
        count ++;
      }
      x++;
    }

	//return true if there are two or more commas
    if (count >= 2){
      return 1;
    }

    else return 0;
}

loglist_t * addLast(loglist_t * list, logline_t templogline){
    /* Declare temp struct  here */
    loglist_t * tempStruct = (loglist_t*)malloc(sizeof(loglist_t));

	//Allocate mem for tempStruct
    if (tempStruct == NULL){
      fprintf(stderr, "Failed to allocated memory newNode.\n");
      exit(-1);
    }

	//Declaring tempStruct
	tempStruct->line = templogline;
	tempStruct->next = NULL;

    //check for first insertion
    if(list == NULL){
      list = tempStruct;
      return list;
    }
    else{
      //initalizes all the temp variables
      loglist_t * temp = list;

	  //While there are more structs in the list
      while (temp -> next != NULL){
        temp = temp->next;
      }

	  //Found end, add to it
      temp->next = tempStruct;
      return list;
    }
}

// prints the the data from resultlist into the output file named combinedlogs.log
void printToFile( loglist_t * head, FILE * outputFile){

	if (head == NULL){// if the head is equal to NULL, return nothing
		printf("Empty List\n");
		return;
	}
	//initalizes all the temp variables, memory allocation.
	loglist_t * temp = malloc(sizeof(loglist_t));
	if (temp == NULL){
		fprintf(stderr, "Unable to allocate memory for new temp structure.\n");
		exit(-1);
	}
	temp = head -> next;
	//prints the data elements of the head, which include the level, message, and the timestamp
	// repeats the same process, but for the rest of the linked list.
	while(temp!=NULL)
    {
    	fprintf(outputFile, "%s,%s,%s", temp->line.level, temp->line.timestamp, temp->line.message);
      temp=temp->next;
    }
}

//Swaps loglist nodes A and B
void swap(loglist_t * a, loglist_t * b) {
	logline_t data = a->line; //This is the line that gets swapped
	a->line = b->line;
	b->line = data;
}
