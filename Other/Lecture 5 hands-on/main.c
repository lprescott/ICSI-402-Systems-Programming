#include <stdio.h>
#include <stdlib.h>

void main( int argc, char *argv[] )  {

   if( argc == 2 ) {
      printf("The input file supplied is \"%s\"\n", argv[1]);

      long pos;
      FILE * fp;
      fp = fopen(argv[1], "r");

      if (fp == NULL) printf("\nThe file cannot be opened.\n");

      else printf("\nThe file has been opened successfully.\n");

      // Print the first character.
      fseek(fp, 0, SEEK_SET);
      pos = ftell(fp);
      printf("The character in the %ld position is %c.", pos, getc(fp));

      //Print the character with offset = 5 from the beginning (also print the offset value)
      fseek(fp, 4, SEEK_SET);
      pos = ftell(fp);
      printf("The character in the %ld position is %c.", pos, getc(fp));

      //Print the character whose offset is 3 plus the current offset (also print the offset value)
      fseek(fp, 2, SEEK_CUR);
      pos = ftell(fp);
      printf("The character in the %ld position is %c.", pos, getc(fp));

      //Print the character whose offset is 4 less thatn the current offset (also print the offset value)
      fseek(fp, -3, SEEK_CUR);
      pos = ftell(fp);
      printf("The character in the %ld position is %c.", pos, getc(fp));

      //Close the input file
      fclose(fp);

   }
   else if( argc > 2 ) {
      printf("Too many arguments supplied.\n");

   }
   else {
      printf("One argument expected.\n");
   }
}
