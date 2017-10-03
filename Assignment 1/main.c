//Project: Prog1
//Names:   Luke Prescott, Rob Rose, Tommy Li
//Roles:   Leader, Monitor, Recorder Respectively
//Date:    10/3/2017
//Course:  ICSI 402
//Desc:    This program takes directory full of log files then concatonates them into
//         a single log file, where the order is based on the time of each log.

#include <stdio.h>
#include <string.h>
#include "protoOne.h"
#include "protoTwo.h"

struct logline{
  char level[20];
  char timestamp[20];
  char message[100];
} logline_t;

typedef struct loglist {
  logline_t line;
  struct loglist *next;
} loglist_t;

int main(void) {

}
