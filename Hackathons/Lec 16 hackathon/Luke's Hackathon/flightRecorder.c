//Imported libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Imported headers

//Typedef'd structure
typedef struct flight{
    char AirlineCodeAndFlightNumber [8]; //AAA1234 + '/0'
    char OriginAirportCode[4]; //JFK + '/0'
    char DestinationAirportCode[4]; //ORL + '/0'
    char DepartureDayOfWeek[4]; //WED + '/0'
    char DepartureMonth[4]; //JAN + '/0'
    int DepartureDay;
    char DepartureTime[6]; //10:00 + '/0'
    int DepartureYear;
} flight;

//Prototypes
long fileSize(FILE * file);

int main( int argc, const char* argv[] )
{
    int flag = 1;
    int sizeOfFlight = sizeof(flight);
    int sizeOfTotalFlight = sizeOfFlight + 8;

    printf("The size of one flight is: %d.\n", sizeOfFlight);
    printf("The size of one flight including 8 1-byte spaces is: %d.\n", sizeOfTotalFlight);

    //(a) Create a binary file to store info about up to 100 flights from a txt file
    FILE * flightData;

    if (flightData == NULL){
        fprintf(stderr, "Could not allocate for * flightData.\n");
    }

    //(b) Read input from user (i.e., create a menu)
    printf("\nThe possible commands are as follows: \n0 to end; \n1 to store info; \n2 to print info; \n3 to count airlines; \n4 to print inbound flights at airport x; \n5 to print inbound flights for all airports; \n6 to print sorted list of origin airports; \n7 to print origin airports with at least 2 flights with departures before noon.\n");
    printf("Your input: ");
    int input;

    while(flag){
        fflush(stdin); scanf("%d", &input);
        if(input == 0){
            //End
            printf("\nThe program will end.");
            flag = 0;
        }
        else if(input == 1){
            flightData = fopen("flightData.bin", "ab");

            flight tempFlight;
            
            char tempAirlineCodeAndFlightNumber [8]; //AAA1234 + '/0'
            char tempOriginAirportCode[4]; //JFK + '/0'
            char tempDestinationAirportCode[4]; //ORL + '/0'
            char tempDepartureDayOfWeek[4]; //WED + '/0'
            char tempDepartureMonth[4]; //JAN + '/0'
            int tempDepartureDay;
            char tempDepartureTime[6]; //10:00 + '/0'
            int tempDepartureYear;

            printf("\nThe program will take a flight to add here.\n");
            printf("Please enter airline code and flight number: ");
            fflush(stdin); scanf("%s", tempAirlineCodeAndFlightNumber);
            //printf("The length is: %d.\n", strlen(tempAirlineCodeAndFlightNumber) + 1);
            strcpy(tempFlight.AirlineCodeAndFlightNumber, tempAirlineCodeAndFlightNumber);

            printf("Please enter Origin Airport Code: ");
            fflush(stdin); scanf("%s", tempOriginAirportCode);
            //printf("The length is: %d.\n", strlen(tempOriginAirportCode) + 1);
            strcpy(tempFlight.OriginAirportCode, tempOriginAirportCode);

            printf("Please enter Destination Airport Code: ");
            fflush(stdin); scanf("%s", tempDestinationAirportCode);
            //printf("The length is: %d.\n", strlen(tempDestinationAirportCode) + 1);
            strcpy(tempFlight.DestinationAirportCode, tempDestinationAirportCode);

            printf("Please enter departure day of week: ");
            fflush(stdin); scanf("%s", tempDepartureDayOfWeek);
            //printf("The length is: %d.\n", strlen(tempDepartureDayOfWeek) + 1);
            strcpy(tempFlight.DepartureDayOfWeek, tempDepartureDayOfWeek);

            printf("Please enter departure month: ");
            fflush(stdin); scanf("%s", tempDepartureMonth);
            //printf("The length is: %d.\n", strlen(tempDepartureMonth) + 1);
            strcpy(tempFlight.DepartureMonth, tempDepartureMonth);

            printf("Please enter departure day: ");
            fflush(stdin); scanf("%d", &tempDepartureDay);
            tempFlight.DepartureDay = tempDepartureDay;

            printf("Please enter departure time: ");
            fflush(stdin); scanf("%s", tempDepartureTime);
            //printf("The length is: %d.\n", strlen(tempDepartureTime) + 1);
            strcpy(tempFlight.DepartureTime, tempDepartureTime);

            printf("Please enter departure year: ");
            fflush(stdin); scanf("%d", &tempDepartureYear);
            tempFlight.DepartureYear = tempDepartureYear;

            printf("\nThe values of the newly created flight:\n");
            printf("AirlineCodeAndFlightNumber: \"%s\".\n", tempFlight.AirlineCodeAndFlightNumber);
            printf("OriginAirportCode: \"%s\".\n", tempFlight.OriginAirportCode);
            printf("DestinationAirportCode: \"%s\".\n", tempFlight.DestinationAirportCode);
            printf("DepartureDayOfWeek: \"%s\".\n", tempFlight.DepartureDayOfWeek);
            printf("DepartureMonth: \"%s\".\n", tempFlight.DepartureMonth);
            printf("DepartureDay: \"%d\".\n", tempFlight.DepartureDay);
            printf("DepartureTime: \"%s\".\n", tempFlight.DepartureTime);
            printf("DepartureYear: \"%d\".\n", tempFlight.DepartureYear);

            fwrite(&tempFlight, sizeof(flight), 1, flightData);

            fclose(flightData);
            printf("\nYour input: ");
        }
        else if(input == 2){
            //(c) Read and print info about all flight records in the file

            flightData = fopen("flightData.bin", "rb");

            long archiveSize = fileSize(flightData);
            int numOfFlights = archiveSize / sizeof(flight);
            printf("Number of flights: %ld/%d = %d.\n", archiveSize, sizeof(flight), numOfFlights);

            rewind(flightData);

            int i = 0;
            for (i; i < numOfFlights; i++){
                flight tempFlight;
                fread(&tempFlight, sizeof(tempFlight), 1, flightData);

                printf("\nFlight #%d:\n", i+1);
                printf("AirlineCodeAndFlightNumber: \"%s\".\n", tempFlight.AirlineCodeAndFlightNumber);
                printf("OriginAirportCode: \"%s\".\n", tempFlight.OriginAirportCode);
                printf("DestinationAirportCode: \"%s\".\n", tempFlight.DestinationAirportCode);
                printf("DepartureDayOfWeek: \"%s\".\n", tempFlight.DepartureDayOfWeek);
                printf("DepartureMonth: \"%s\".\n", tempFlight.DepartureMonth);
                printf("DepartureDay: \"%d\".\n", tempFlight.DepartureDay);
                printf("DepartureTime: \"%s\".\n", tempFlight.DepartureTime);
                printf("DepartureYear: \"%d\".\n", tempFlight.DepartureYear);
            }

            fclose(flightData);
            printf("\nYour input: ");
        }
        else{
            //End
            printf("\nThe program will end.");
            flag = 0;
        }
    }

    //(c) Read and print info about all flight records in the file
    //(d) Count number of airlines for a given airport
    //(e) Print the number of inbound flights for airport x
    //(f) Print the number of inbound flights for each airport
    //(g) Print a sorted list of origin airports based on the number of outbound flights
    //(h) Print a list of origin airports that have at least 2 flights that have a departure time earlier than noon

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