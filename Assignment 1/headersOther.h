#include "structs.h"

#ifndef HEADERSOTHER_H
#define HEADERSOTHER_H

//int looksCorrect(tempLine);
int containsTwoPlusCommas(char * line);
loglist_t * addLast(loglist_t * list, logline_t templogline);
void printToFile( loglist_t * head, FILE * outputFile);

#endif
