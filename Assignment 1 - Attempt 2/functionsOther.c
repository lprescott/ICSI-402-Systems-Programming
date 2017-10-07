#include <string.h>

#include "structs.h"
#include "headersOther.h"

char * getExtension(char * fileName){
    char * dot;
    dot = strchr(fileName, '.');
    return dot;
}