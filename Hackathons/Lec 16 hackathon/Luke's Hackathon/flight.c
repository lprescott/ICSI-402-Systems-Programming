#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "headers.h"
#include "structs.h"



flight * createFlight( char * AirlineCodeAndFlightNumber, char * OriginAirportCode, char * DestinationAirportCode, char * DepartureDayOfWeek, char * DepartureMonth, int DepartureDay, char * DepartureTime, int DepartureYear) {

  flight * tempFlight = malloc(sizeof(flight));

  strcpy(tempFlight->AirlineCodeAndFlightNumber, AirlineCodeAndFlightNumber);
  strcpy(tempFlight->OriginAirportCode, OriginAirportCode);
  strcpy(tempFlight->DestinationAirportCode, DestinationAirportCode);
  strcpy(tempFlight->DepartureDayOfWeek, DepartureDayOfWeek);
  strcpy(tempFlight->DepartureMonth, DepartureMonth);
  strcpy(tempFlight->DepartureTime, DepartureTime);

  tempFlight->DepartureDay = DepartureDay;
  tempFlight->DepartureYear = DepartureYear;

  return tempFlight;
}

void printDetails(FILE * archive){
  long archiveSize = fileSize(archive);
  long numOfFlights = archiveSize / (sizeof(flight) + 8);
  
  int i = 0;
  for(i; i < numOfFlights; i++){

	flight * tempFlight = malloc(sizeof(flight));
	
	fread(tempFlight->AirlineCodeAndFlightNumber, sizeof(tempFlight->AirlineCodeAndFlightNumber), 1, archive);
	fseek(archive, 1, SEEK_CUR);
	fread(tempFlight->OriginAirportCode, sizeof(char), 3, archive);
	fseek(archive, 1, SEEK_CUR);
	fread(tempFlight->DestinationAirportCode, sizeof(char), 3, archive);
	fseek(archive, 1, SEEK_CUR);
	fread(tempFlight->DepartureDayOfWeek, sizeof(char), 3, archive);
	fseek(archive, 1, SEEK_CUR);
	fread(tempFlight->DepartureMonth, sizeof(char), 3, archive);
	fseek(archive, 1, SEEK_CUR);
	fread(&tempFlight->DepartureDay, sizeof(int), 1, archive);
	fseek(archive, 1, SEEK_CUR);
	fread(tempFlight->DepartureTime, sizeof(char), 5, archive);
	fseek(archive, 1, SEEK_CUR);
	fread(&tempFlight->DepartureYear, sizeof(int), 1, archive);
	fseek(archive, 1, SEEK_CUR);

	printf("The flight: \"%d\".\n", i+1);
        printf("The airline code is: \"%s\".\n", tempFlight->AirlineCodeAndFlightNumber);
	printf("The origin airport code: %s.\n", tempFlight->OriginAirportCode);
	printf("The dest. airport code: %s.\n", tempFlight->DestinationAirportCode);
	printf("The departure day of the week: %s.\n", tempFlight->DepartureDayOfWeek);
	printf("The departure month %s.\n", tempFlight->DepartureMonth);
	printf("The departure day: %d.\n", tempFlight->DepartureDay);
	printf("The departure time: %s.\n", tempFlight->DepartureTime);
	printf("The departure year: %d.\n\n", tempFlight->DepartureYear);
  }
}

/*
  This function finds file size by seeking all the way to the end on the file, then telling the long
  position the position of the end character. This position is the size of the file in bytes. It only takes,
  one argument, which is the FILE type needed to point to.
*/
long fileSize(FILE * file){
    //Position: the variable to be returned, and the position of the end character.
    unsigned long endPosition = 0;
    unsigned long startPosition = 0;

    fflush(file); //Flush the buffer
    startPosition = ftell(file); //Record the start pos.

	// if it is null, and error is printed and terminates
    if (file == NULL){
        fprintf(stderr, "Error opening file in fileSize().\n");
        return(-1);
    }

    fseek(file, 0, SEEK_END);// sets the file position of the stream to the given offset

    endPosition = ftell(file);// ftell returns the current file postion of the given stream, and that is the value of position.

    fseek(file,startPosition,SEEK_SET); //return to start position

    return endPosition;// returns the position of the file offset
}
