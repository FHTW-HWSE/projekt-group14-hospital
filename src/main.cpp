#include <stdio.h>
#include <stdlib.h>
//#include "../include/CSV_read.h"
#include "../include/CSV_write.h"
#include "../include/dateFunctions.h"
#include "../include/definitions.h"
#include <catch2/catch.hpp>
#include <string.h>

#pragma region delaration of all functions
void printOutMap(int (*seatingMap)[MAP_ROWS]);
/**
 * @brief Displays a menu and handles user input.
 *
 * This function displays a menu with several options and waits for the user to input a single character to select an option.
 * Depending on the selected option, a corresponding function is called or an error message is displayed.
 * This function continues to display the menu until the user selects the "quit" option or an error occurs.
 *
 * @return 1 if the program should be closed, -1 if an error occurred.
 */
int menu();
/**
 * @brief The declaration of error messages
 *
 * Depending on enum error it prints out the correct error message
 *
 * @param check enum error code
 *
 * @return  string, containing the correct messages
 */
const char *printErrorMsg(int error_code);
int readInPatientData(int elementCount, char ** returnWord);
#pragma endregion


#pragma region MAIN
int main(int argc, char *argv[])
{

PatientRecord* patienttest;

patienttest = searchPatientInCSV(1234567890);
printf("SSN: %lu\n", patienttest->ssn);
printf("Name: %s\n", patienttest->name);
printf("Arrival Time: %d\n", patienttest->arrivalTime);
printf("Arrival Date: %ld\n", patienttest->arrivalDate);
printf("Departure Time: %d\n", patienttest->departureTime);
printf("Departure Date: %ld\n", patienttest->departureDate);
printf("Infectious: %c\n", patienttest->infectious);
printf("Seating Number: %d\n", patienttest->seatingNumber);
return 0;

/* Test Writefunction Michi
writePatientData(
    1234567890,
    "Hans",
    1236,
    1234587,
    1234,
    1234578,
    'Y',
    123,
    1
    );
return 0;*/



#pragma region test for time func
/*------------test für time-----------------*/
    int myTime = 0;
    time_t now;
    struct tm *timeInfo;

    time(&now);
    timeInfo = localtime(&now);

    myTime = getTime(timeInfo);
    printf("\n ---- Test für time fkt (to be deleted!)\n %d \n ---- end test time\n",myTime);
#pragma endregion
   
    char *buffer = (char *)malloc(sizeof(char) * 1000);
    if (buffer == NULL){
       fprintf(stderr, "%s", printErrorMsg(ERR_MALLOC));
       return 1;
    }

    /* TODO new functions... 
    buffer = read_csv("test.csv"); 
    printf("%s", buffer);
    */

    /*------Initalize seating map-------*/
    int seatingMap[MAP_ROWS][MAP_COLUMNS];
    int num = 1;
    for (int i = 0; i < MAP_ROWS; i++) {
        for (int j = 0; j < MAP_COLUMNS; j++) {
            seatingMap[i][j] = num;
            num++;
        }
    }
    printOutMap(seatingMap);
    /*-----------------------------*/
   

    menu(); //note: func.returns:1=user wants to close program/-1=too many wrong inputs from user
    free(buffer);

    return 0;
}//end main

#pragma endregion MAIN


//// READ IN PATIENT DATA ####################################
//general function to read in patient data
  int readInPatientData(int elementCount, char ** returnWord){
    int checkDefault = 0;
 
    fgets(*(returnWord), elementCount+2, stdin);
    //Error handling if user enters too many characters
    if (*(returnWord)[elementCount - 1] != '\n') {
        while (getchar() != '\n'); // to catch all characters if user enters too many
        printf("Your input could not be processed! Please enter only %d characters");
  }
  return 0;
  }




void printOutMap(int (*seatingMap)[MAP_ROWS]){

    printf("  Seating Map\n\n"); 

    for (int i = 0; i < MAP_ROWS; i++) {
        printf("------------------------------\n|");
        for (int j = 0; j < MAP_COLUMNS; j++) {
            if(seatingMap[i][j] == 0){          //if 0, seat number is occupied -> print X
                printf("  X | ");
            }
            else{ 
            printf(" %2d | ", seatingMap[i][j]);
            }
        }
        printf("\n");
    }
    printf("------------------------------\n|");
}

//maybe some splitting up would be nice haha :(
// no idea if it works, TBC
int addNewPatient() {
    PatientRecord tempPatient = {0, "", 0, 0, 0, 0, 'N', 0};
    
    bool seatTaken[MAP_ROWS * MAP_COLUMNS] = {false};

    int checkDefault = 0;
    printf("Please enter the patients social security number (FORMAT: 0000YYMMDD)\n");

    while (scanf("%lu", &tempPatient.ssn) != 1) {
        printf("Invalid input. Please enter a valid social security number (FORMAT: 0000YYMMDD):\n");
        while (getchar() != '\n');
    }
    getchar(); // remove the trailing newline character

    printf("\nPlease enter the patients name (FORMAT: Surname Forename)\n");
    fgets(tempPatient.name, MAX_PATIENT_NAME, stdin);
    tempPatient.name[strcspn(tempPatient.name, "\n")] = 0; // Remove newline character from the string

    int attempts = 0;
    printf("\nIs the patient infectious? [Y/N]\n");
    while (1) {
        char c = getchar();
        if (getchar() != '\n') {
            while (getchar() != '\n'); // discard extra characters
        }
        switch (tolower(c)) {
            case 'y':
                tempPatient.infectious = 'Y';
                break;
            case 'n':
                tempPatient.infectious = 'N';
                break;
            default:
                attempts++;
                if (attempts >= 3) {
                    printf("Invalid input entered too many times. Exiting...\n");
                    return -1;
                }
                printf("Invalid input! Please enter 'Y' or 'N':\n");
                continue;
        }
        break;
    }



    printf("\nPlease press 'a' if the patient came by ambluance or 'o' if they came by themself\n");
    while (1) {
        char c = getchar();
        if (getchar() != '\n') {
            while (getchar() != '\n');
        }
        switch (tolower(c)) {
            case 'a':
                printf("Patient by ambulance TBD\n");
                tempPatient.seatingNumber = -1;
                tempPatient.infectious = 'N';
                break;
            case 'o':
                printf("Patient by themself TBD\n");
                // TO DO: getTime & Date + save
                // TO DO: ask seating number

                printf("\nPlease enter the seating number (1-%d):\n", MAP_ROWS * MAP_COLUMNS);
                    while (1) {
                        int result = scanf("%d", &tempPatient.seatingNumber);
                        while (getchar() != '\n'); // discard extra characters

                        if (result == 1 && tempPatient.seatingNumber >= 1 && tempPatient.seatingNumber <= (MAP_ROWS * MAP_COLUMNS)) {
                            if (seatTaken[tempPatient.seatingNumber - 1]) {
                                printf("Seat %d is already taken! Please enter another seating number (1-%d):\n", tempPatient.seatingNumber, MAP_ROWS * MAP_COLUMNS);
                            } else {
                                seatTaken[tempPatient.seatingNumber - 1] = true;
                                break;
                            }
                        } else {
                            printf("Invalid input! Please enter a valid seating number between 1 and %d:\n", MAP_ROWS * MAP_COLUMNS);
                        }
                    }

                break;
            default:
                checkDefault++;
                if (checkDefault > 10) {
                    printf("Your input could not be processed for the %dth time...\n"
                           "closing adding new patient...\n\n\n", checkDefault);
                    return -1;
                }
                printf("Your input could not be processed! Please enter only one character\n\n");
                continue;
        }
        break;
    }

    // TODO Write tempPatient to file
    // writePatientData(tempPatient);
/*TESTPRINT*/
    printf("Patient Record:\n"
       "SSN: %lu\n"
       "Name: %s\n"
       "Arrival Time: %d\n"
       "Arrival Date: %ld\n"
       "Departure Time: %d\n"
       "Departure Date: %ld\n"
       "Infectious: %c\n"
       "Seating Number: %d\n",
       tempPatient.ssn, tempPatient.name, tempPatient.arrivalTime, tempPatient.arrivalDate,
       tempPatient.departureTime, tempPatient.departureDate, tempPatient.infectious, tempPatient.seatingNumber);


    return 0;
}






int menu() {
    int static checkDefault = 0;

    while (1) {
        printf("You are now in the menu...\n"
               "\t- Press 'n' to create a new patient\n"
               "\t- Press 'p' to show the prioritization list\n"
               "\t- Press 'c' to change the data of a patient\n"
               "\t- Press 'i' to display infectious patients incl. seat neighbors\n"
               "\t- Press 's' to display the current seating arrangements\n"
               "\t- Press 'q' to close the program\n");

        int c = getchar();
        if (getchar() != '\n') {
            while (getchar() != '\n'); // to catch all characters if user enters too many
        }

        switch (c) {
            /***Create new patient***/
            case 'n':
                printf("tbd Funktionsaufruf new patient\n");
                if(addNewPatient() == 0) printf("patient saved successfully!\n");
                break;
            /***Showing priorization list***/
            case 'p':
                printf("tbd Funktionsaufruf display priorization list\n");
                break;
            /***Change patients date***/
            case 'c':
                printf("tbd Funktionsaufruf change patient data\n");
                break;
            /***Display infectious patients incl. seat neighbors***/
            case 'i':
                printf("tbd Funktionsaufruf display infectious patients incl. seat neighbors\n");
                break;
            /***Display the current seating arrangements***/
            case 's':
                printf("tbd Funktionsaufruf display the current seating arrangements\n");
                break;
            /***Close program***/
            case 'q':
                printf("You chose to close the program ... bye!\n\n");
                return 1;
            /***Default: Wrong input -> entering again menu***/
            default:
                checkDefault++;
                if (checkDefault > 10) {
                    printf("Your input could not be processed for the %dth time...\n"
                           "closing program, bye!!!\n\n\n", checkDefault);
                    return -1;
                }
                printf("Your input could not be processed! Please enter only one character\n\n");
                continue;
        }
    }
}




const char *printErrorMsg(int error_code) {
    switch (error_code)
    {
    case ERR_CLOSING_FILE:
        return "An error occurred while closing a file\n";
    case ERR_OPENING_FILE:
        return "An error occurred while opening a file\n";
    case ERR_MALLOC:
        return "Error allocating memory\n";

    default:
        return "No error message was found\n";
    }
}


