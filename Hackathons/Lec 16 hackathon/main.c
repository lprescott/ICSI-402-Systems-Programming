#include <stdio.h>

#include "structs.h"

int main( int argc, const char* argv[] )
{
    //(a) Create a binary file to store info about up to 100 flights from a txt file
    //(b) Read input from user (i.e., create a menu)
    //(c) Read and print info about all flight records in the file
    //(d) Count number of airlines for a given airport
    //(e) Print the number of inbound flights for airport x
    //(f) Print the number of inbound flights for each airport
    //(g) Print a sorted list of origin airports based on the number of outbound flights
    //(h) Print a list of origin airports that have at least 2 flights that have a departure time earlier than noon

	printf( "\nHello World\n\n" );
}

flight * createFlight( char * AirlineCodeAndFlightNumber, char * OriginAirportCode, char * DestinationAirportCode, char * DepartureDayOfWeek ,char * DepartureMonth, int DepartureDay, char * DepartureTime, int DepartureYear) {

    flight * tempFlight = malloc(sizeof(flight));

    tempFlight->AirlineCodeAndFlightNumber = strdup(AirlineCodeAndFlightNumber);
    tempFlight->OriginAirportCode = strdup(OriginAirportCode);
    tempFlight->DestinationAirportCode = strdup(DestinationAirportCode);
    tempFlight->DepartureDayOfWeek = strdup(DepartureDayOfWeek);
    tempFlight->DepartureMonth = strdup(DepartureMonth);
    tempFlight->DepartureTime = strdup(DepartureTime);
    tempFlight->DepartureDay = DepartureDay;
    tempFlight->DepartureYear = DepartureYear;

    return tempFlight;
  }
