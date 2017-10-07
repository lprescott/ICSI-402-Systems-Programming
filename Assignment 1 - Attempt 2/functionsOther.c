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

void add(loglist_t ** head, logline_t line){
    
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

    loglist_t * temp = * head;
    if (*head = NULL){
        *head=newNode;
    }

    else{
        while(temp->next!=NULL){
            temp=temp->next;
        }

        temp->next=newNode;
    }
    return;
} /*End insert */
