#include <string.h>

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