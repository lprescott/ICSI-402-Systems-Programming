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
int checkIfContains(char fileNames[100][4], int numFiles, char name[4]);

int main( int argc, const char* argv[] )
{
    int flag = 1;
    int sizeOfFlight = sizeof(flight);
    int sizeOfTotalFlight = sizeOfFlight + 8;

    printf("The size of one flight is: %d.\n", sizeOfFlight);
    printf("The size of one flight including 8 1-byte spaces is: %d.\n", sizeOfTotalFlight);

    //(a) Create a binary file to store info about up to 100 flights from a txt file
    FILE * flightData;

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

            flight tempFlight;
			
            char tempAirlineCodeAndFlightNumber [8]; //AAA1234 + '/0'
            char tempOriginAirportCode[4]; //JFK + '/0'
            char tempDestinationAirportCode[4]; //ORL + '/0'
            char tempDepartureDayOfWeek[4]; //WED + '/0'
            char tempDepartureMonth[4]; //JAN + '/0'
            int tempDepartureDay;
            char tempDepartureTime[6]; //10:00 + '/0'
            int tempDepartureYear;
            int length;

            printf("\nThe program will take a flight to add here.\n");
            printf("Please enter airline code and flight number: ");
            fflush(stdin); scanf("%s", tempAirlineCodeAndFlightNumber);
            length = strlen(tempAirlineCodeAndFlightNumber) + 1;
            if (length > 8){
                fprintf(stderr, "The supplied string is too large.\n");
                exit(-1);
            }
            strcpy(tempFlight.AirlineCodeAndFlightNumber, tempAirlineCodeAndFlightNumber);
			
            printf("Please enter Origin Airport Code: ");
            fflush(stdin); scanf("%s", tempOriginAirportCode);
            length = strlen(tempOriginAirportCode) + 1;
            if (length > 8){
                fprintf(stderr, "The supplied string is too large.\n");
                exit(-1);
            }
            strcpy(tempFlight.OriginAirportCode, tempOriginAirportCode);

            printf("Please enter Destination Airport Code: ");
            fflush(stdin); scanf("%s", tempDestinationAirportCode);
            length = strlen(tempDestinationAirportCode) + 1;
            if (length > 8){
                fprintf(stderr, "The supplied string is too large.\n");
                exit(-1);
            }
            strcpy(tempFlight.DestinationAirportCode, tempDestinationAirportCode);

            printf("Please enter departure day of week: ");
            fflush(stdin); scanf("%s", tempDepartureDayOfWeek);
            length = strlen(tempDepartureDayOfWeek) + 1;
            if (length > 8){
                fprintf(stderr, "The supplied string is too large.\n");
                exit(-1);
            }
            strcpy(tempFlight.DepartureDayOfWeek, tempDepartureDayOfWeek);

            printf("Please enter departure month: ");
            fflush(stdin); scanf("%s", tempDepartureMonth);
            length = strlen(tempDepartureMonth) + 1;
            if (length > 8){
                fprintf(stderr, "The supplied string is too large.\n");
                exit(-1);
            }
            strcpy(tempFlight.DepartureMonth, tempDepartureMonth);

            printf("Please enter departure day: ");
            fflush(stdin); scanf("%d", &tempDepartureDay);
            tempFlight.DepartureDay = tempDepartureDay;

            printf("Please enter departure time: ");
            fflush(stdin); scanf("%s", tempDepartureTime);
            length = strlen(tempDepartureTime) + 1;
            if (length > 8){
                fprintf(stderr, "The supplied string is too large.\n");
                exit(-1);
            };
            strcpy(tempFlight.DepartureTime, tempDepartureTime);

            printf("Please enter departure year: ");
            fflush(stdin); scanf("%d", &tempDepartureYear);
            tempFlight.DepartureYear = tempDepartureYear;
			
			//CHECK
			FILE * flightDataRead;
			if ((flightDataRead = fopen("flightData.bin", "rb")) != NULL) {

                long archiveSize = fileSize(flightData);
				int numOfFlights = archiveSize / sizeof(flight);
				
				int i = 0;
				for (i; i < numOfFlights; i++){
					flight tempFlightRead;
					fread(&tempFlightRead, sizeof(tempFlight), 1, flightData);

					if (strcmp(tempFlightRead.AirlineCodeAndFlightNumber, tempFlight.AirlineCodeAndFlightNumber) == 0) {
						if (strcmp(tempFlightRead.OriginAirportCode, tempFlight.OriginAirportCode) == 0) {
							if (strcmp(tempFlightRead.DestinationAirportCode, tempFlight.DestinationAirportCode) == 0) {
								if (strcmp(tempFlightRead.DepartureDayOfWeek, tempFlight.DepartureDayOfWeek) == 0) {
									if (strcmp(tempFlightRead.DepartureMonth, tempFlight.DepartureMonth) == 0) {
										if (tempFlightRead.DepartureDay == tempFlight.DepartureDay) {
											if (strcmp(tempFlightRead.DepartureTime, tempFlight.DepartureTime) == 0) {
												if (tempFlightRead.DepartureYear, tempFlight.DepartureYear) {
													fprintf(stderr, "\nInputed the same flight, exiting now.\n");
													exit(-1);
												}
											}
										}
									}
								}
							}
						}
					}
					
				}

				fclose(flightDataRead);
				//End Check
			
			}
			
            flightData = fopen("flightData.bin", "ab");
            
            long archiveSize = fileSize(flightData);
            int numOfFlights = archiveSize / sizeof(flight);
            printf("Number of flights: %ld/%ld = %d.\n", archiveSize, sizeof(flight), numOfFlights);

            if (numOfFlights > 100){
                fprintf(stderr, "There cannot be more than 100 flights in the archive.");
                exit(-1);
            }

			rewind(flightData);
			
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
            printf("Number of flights: %ld/%ld = %d.\n", archiveSize, sizeof(flight), numOfFlights);

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
        else if(input == 3){
            //(d) Count number of airlines for a given airport
			
			flightData = fopen("flightData.bin", "rb");

            long archiveSize = fileSize(flightData);
            int numOfFlights = archiveSize / sizeof(flight), count = 0;
			char airport[4];
            printf("Number of flights: %ld/%ld = %d.\n", archiveSize, sizeof(flight), numOfFlights);

            if (numOfFlights > 100){
                fprintf(stderr, "There cannot be more than 100 flights in the archive.");
                exit(-1);
            }
			
			printf("\nEnter the airport you would like to count: ");
			
			fflush(stdin); scanf("%s", airport);
			printf("\nYour input: \"%s\"\n", airport);
			
            rewind(flightData);

            int i = 0;
            for (i; i < numOfFlights; i++){
                
				flight tempFlight;
                fread(&tempFlight, sizeof(tempFlight), 1, flightData);
				
				if ((strcmp(airport, tempFlight.DestinationAirportCode) == 0) || (strcmp(airport, tempFlight.OriginAirportCode) == 0)) {
					count++;
				}
				
            }
			
			printf("The number of airlines for a given airport is : \"%d\".\n", count);

            fclose(flightData);
            printf("\nYour input: ");
			
        }
        else if(input == 4){
            //(e) Print the number of inbound flights for airport x
			flightData = fopen("flightData.bin", "rb");

            long archiveSize = fileSize(flightData);
            int numOfFlights = archiveSize / sizeof(flight), count = 0;
			char airport[4];
            printf("Number of flights: %ld/%ld = %d.\n", archiveSize, sizeof(flight), numOfFlights);
			
			printf("\nEnter the airport you would like to count: ");
			
			fflush(stdin); scanf("%s", airport);
			printf("\nYour input: \"%s\"\n", airport);
			
            rewind(flightData);

            int i = 0;
            for (i; i < numOfFlights; i++){
                
				flight tempFlight;
                fread(&tempFlight, sizeof(tempFlight), 1, flightData);
				
				if ((strcmp(airport, tempFlight.DestinationAirportCode) == 0)) {
					count++;
				}
				
            }
			
			printf("The number of airlines for a given airport is : \"%d\".\n", count);

            fclose(flightData);
            printf("\nYour input: ");

        }
        else if(input == 5){
            //(f) Print the number of inbound flights for each airport

            //Loop through every flight, looking for new DESTINATION airports
            //Adding them to an inorder array of strings
            //Incrementing a array list at that index
            flightData = fopen("flightData.bin", "rb");
            
            long archiveSize = fileSize(flightData);
            int numOfFlights = archiveSize / sizeof(flight);
            printf("Number of flights: %ld/%ld = %d.\n", archiveSize, sizeof(flight), numOfFlights);

            char destinations[100][4];
            //Loop through the array initializing to empty vals
            int x = 0;
            for (x; x < 100; x ++){
                strcpy(destinations[x], "\0\0\0\0");
            }

            int destinationCounts[100];
            for (x = 0; x < 100; x ++){
                destinationCounts[x] = 0;
            }  

            rewind(flightData);

            int i = 0; int index = 0; int tempIndex = 0;
            for (i; i < numOfFlights; i++){
                flight tempFlight;
                fread(&tempFlight, sizeof(tempFlight), 1, flightData);

                //int checkIfContains(char ** fileNames, int numFiles, char * name)
                if((tempIndex = checkIfContains(destinations, 100, tempFlight.DestinationAirportCode)) == -1){
                    //Does not exist in array
                    strcpy(destinations[index], tempFlight.DestinationAirportCode);
                    destinationCounts[index] += 1;
                    index ++;
                }
                else{
                    //Exists in array
                    destinationCounts[tempIndex] += 1;
                }
            }

            fclose(flightData);

            //Print
            i  =  0;
            while((strcmp(destinations[i], "\0\0\0\0") != 0) && (i < 100)){
                printf("Airport: %s; Number of inbound flights: %d.\n", destinations[i], destinationCounts[i]);
                i++;
            }

            printf("\nYour input: ");
        }
        else if(input == 6){
            //(g) Print a sorted list of origin airports based on the number of outbound flights

        }
        else if(input == 7){
            //(h) Print a list of origin airports that have at least 2 flights that have a departure time earlier than noon
            
        }
        else{
            //End
            printf("\nThe program will end.");
            flag = 0;
        }
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

/*
    This function loops through entire array, and if name is == fileNames the function returns the index, else it returns -1;
    For parameters, this functions takes the string array of file names, the number of files, and the name to use in comparisons.
*/
int checkIfContains(char fileNames[100][4], int numFiles, char name[4]) {
	//i for loop
	int i;
  //This loops through the number of files supplied, comparing the string at the index with name
  //returning the location (index) of the correct file name.
	for (i = 0; i < numFiles; i++) {
		if (strcmp(fileNames[i], name) == 0) {
			//printf("\n index Given : %d", i);
			return i;
		}
	}

  //If nothing else it returns -1
	return -1;
}