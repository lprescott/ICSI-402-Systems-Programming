/*
    This header file contains only symbolic constants. 
*/

//True and false are equal to 1 and 0, respectively.
#define true 1
#define True 1
#define false 0
#define False 0

/*
1. The number of files, N, is a 4-byte unsigned integer.
2. The size of each file is a 4-byte unsigned integer.
3. The length of each filename is 1 <= li <= 255 (i.e., can be stored as a 1-byte unsigned char).
4. The filename takes up exactly li + 1 bytes in the archive (each character takes up 1 byte,
   including the null-terminating character).
*/

#define SizeOfNumOfFiles 4 //1
#define SizeOfFileLength 1//2
#define SizeOfTheFile 4 //3
#define SizeOfFileName 256 //4