//Project: Prog1
//Names:   Luke Prescott, Rob Rose, Tommy Li
//Roles:   Leader, Monitor, Recorder Respectively
//Date:    10/3/2017
//Course:  ICSI 402
//Desc:    This file contains the functions mergeLists and sortList to be used in main.c 

/*merges the sorted link list "inlist" into "resultlist" 
and it returns a pointer to the head of the combined list
*/
loglist* mergeLists(loglist* resultlist, loglist* inlist);

/* use either a concatenation function where the two log files are listed
into one major file, or create named create a new file named resultlist, then
open contents of each files, and copy the contents into each file into result list.
*?

//http://www.geeksforgeeks.org/c-program-merge-contents-two-files-third-file/


/*sorts the provided linked list inlist and 
returns a pointer to the head of sorted list 
*/
loglist* sortList(loglist* inlist);
