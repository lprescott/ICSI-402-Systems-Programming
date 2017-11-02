#include "structs.h"


void printDetails(FILE * archive);
int countAirlines(FILE * archive, int numOfFlights, char * airport);
int inboundFlightsForOne(FILE * archive, int numOfFlights, char * airport);
void inboundFlightsForAll(FILE * archive, int numOfFLights);
void printOrderedList(FILE * archive, int numOfFlights);
void printSpecificOrigin(FILE * archive, int numOfFlights);
flight * createFlight(char * AirlineCodeAndFlightNumber, char * OriginAirportCode, char * DestinationAirportCode, char * DepartureDayOfWeek, char * DepartureMonth, int DepartureDay, char * DepartureTime, int DepartureYear);
long fileSize(FILE * file);
