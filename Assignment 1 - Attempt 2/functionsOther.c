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

void add(loglist_t * head, logline_t line){
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

    //check for first insertion
    if(head->next == NULL){
        head->next = newNode;
        printf("added at beginning\n");
    }

    else
    {
        //else loop through the list and find the last
        //node, insert next to it
        loglist_t * current = head;
        while (current->next != NULL) {
        current = current->next;
        }
        current->next = newNode;
        printf("added later\n");
    }

} /*End insert */
