#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "structs.h"
#include "headersOther.h"

int isLogFile(char * fileName){
    char * dot;
    dot = strchr(fileName, '.');
    if(strcmp(dot, ".log") == 0){
        return 1;
    }

    else{
        return 0;
    }
}

int containsCommas(char * line){
    if (strstr(line, ",") != NULL) return 1;
    else return 0;
}

<<<<<<< HEAD
void add(loglist_t * head, logline_t line){

=======
<<<<<<< HEAD
void add(loglist_t * head, logline_t line){
<<<<<<< HEAD
=======
=======
void add(loglist_t ** head, logline_t line){
>>>>>>> f1bdcd3f9a64d51c0b4043ca102f14773b217b0c
    
>>>>>>> 778a62812e164976181b07d0658ad468036a2e71
>>>>>>> 6beb557d8b1e925573924276651d683c7d870cb8
    loglist_t * newNode = (loglist_t*)malloc(sizeof(loglist_t));
    logline_t * newLine = (logline_t*)malloc(sizeof(logline_t));

    if(newNode == NULL){
        fprintf(stderr, "Unable to allocate memory for new node\n");
        exit(-1);
    }

    if(newLine == NULL){
        fprintf(stderr, "Unable to allocate memory for new line\n");
        exit(-1);
    }

    strcpy(newLine->level , line.level);
    strcpy(newLine->timestamp , line.timestamp);
    strcpy(newLine->message , line.message);

    newNode->line = * newLine;
    newNode->next = NULL;

    if(head == NULL){
        head = newNode;
        return;
    }


    while(head->next != NULL){
        head = head -> next;
    }

    head = newNode;


    return;
} /*End insert */