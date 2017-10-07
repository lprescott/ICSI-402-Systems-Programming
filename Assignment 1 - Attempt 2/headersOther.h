#include "structs.h"

#ifndef HEADERSOTHER_H
#define HEADERSOTHER_H

int isLogFile(char * fileName);
int containsCommas(char * line);
void insert(loglist_t * head, logline_t line);

#endif