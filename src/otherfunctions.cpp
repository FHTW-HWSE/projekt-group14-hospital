#include "../include/otherfunctions.h"
#include "../include/CSV_read.h"
#include "../include/CSV_write.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/dateFunctions.h"
#include <ctype.h>

PatientRecord *findPatient(PatientList *head, unsigned long soz) {
    PatientList *patient = head;
    
    while(patient != NULL) {
        
        if(patient->data->ssn == soz) {
            return patient->data;
        }
        patient = patient->next;
    } 
    return NULL;
}


//////////////////////////////////////////////////////////////////////////////////////////
//Valentina von Main

void printOutMap(Seat seatingMap[MAP_ROWS][MAP_COLUMNS]) {
    printf("  Seating Map\n\n");

    for (int i = 0; i < MAP_ROWS; i++) {
        printf("------------------------------\n|");
        for (int j = 0; j < MAP_COLUMNS; j++) {
            if (seatingMap[i][j].isReserved) {
                printf("  X | ");
            } else {
                printf(" %2d | ", seatingMap[i][j].seatNumber);
            }
        }
        printf("\n");
    }
    printf("------------------------------\n|");
}

/*
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
*/





void initializeSeatingMap(Seat seatingMap[MAP_ROWS][MAP_COLUMNS]) {
    int seatNumber = 1;
    for (int i = 0; i < MAP_ROWS; i++) {
        for (int j = 0; j < MAP_COLUMNS; j++) {
            seatingMap[i][j].seatNumber = seatNumber++;
            seatingMap[i][j].isReserved = false;
        }
    }
}

bool reserveSeatByNumber(int seatNumber, Seat seatingMap[MAP_ROWS][MAP_COLUMNS]) {
    for (int i = 0; i < MAP_ROWS; i++) {
        for (int j = 0; j < MAP_COLUMNS; j++) {
            if (seatingMap[i][j].seatNumber == seatNumber) {
                if (!seatingMap[i][j].isReserved) {
                    seatingMap[i][j].isReserved = true;
                    return true;
                }
                break;
            }
        }
    }
    return false;
}

bool cancelReservationByNumber(int seatNumber, Seat seatingMap[MAP_ROWS][MAP_COLUMNS]) {
    for (int i = 0; i < MAP_ROWS; i++) {
        for (int j = 0; j < MAP_COLUMNS; j++) {
            if (seatingMap[i][j].seatNumber == seatNumber) {
                if (seatingMap[i][j].isReserved) {
                    seatingMap[i][j].isReserved = false;
                    return true;
                }
                break;
            }
        }
    }
    return false;
}




//maybe some splitting up would be nice haha :(
// no idea if it works, TBC
int addNewPatient(Seat seatingMap[MAP_ROWS][MAP_COLUMNS]) {
    PatientRecord tempPatient = {0, "x", 0,0,0,0, 'N'};
    
    //bool seatTaken[MAP_ROWS * MAP_COLUMNS] = {false};

    int checkDefault = 0;
    printf("Please enter the patients social security number (FORMAT: 0000YYMMDD)\n");
//TODO CHECK IF SSN DOUBLE
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
                printf("Patient came by themself - current time & date has been saved!\n");

                tempPatient.arrivalTime = getTime();
                tempPatient.arrivalDate = getDate();

                // TO DO: check if seat is already taken
                printf("\nPlease enter the seating number (1-%d):\n", MAP_ROWS * MAP_COLUMNS);
                    while (1) {
                        int result = scanf("%d", &tempPatient.seatingNumber);
                        while (getchar() != '\n'); // discard extra characters

                        if (result == 1 && tempPatient.seatingNumber >= 1 && tempPatient.seatingNumber <= (MAP_ROWS * MAP_COLUMNS)) {
                            if (reserveSeatByNumber(tempPatient.seatingNumber, seatingMap) == false) {
                                printf("Seat %d is already taken! Please enter another seating number (1-%d):\n", tempPatient.seatingNumber, MAP_ROWS * MAP_COLUMNS);
                            } else {
                                reserveSeatByNumber(tempPatient.seatingNumber, seatingMap);
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
    M_WRITEPATIENTDATASTRUCT((&tempPatient));


/*
    writePatientData(tempPatient.ssn, 
    tempPatient.name, 
    tempPatient.arrivalTime, 
    tempPatient.arrivalDate, 
    tempPatient.departureTime, 
    tempPatient.departureDate, 
    tempPatient.infectious, 
    tempPatient.seatingNumber);

    */
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



int menu(Seat seatingMap[MAP_ROWS][MAP_COLUMNS]) {
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
                if(addNewPatient(seatingMap) == 0) printf("patient saved successfully!\n");
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
                printOutMap(seatingMap);
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


void printErrorMsg(int error_code) {
    switch (error_code)
    {
    case ERR_CLOSING_FILE:
        fprintf(stderr,"An error occurred while closing a file\n");
        return;
    case ERR_OPENING_FILE:
    fprintf(stderr,"An error occurred while opening a file\n");
        return ;
    case ERR_MALLOC:
    fprintf(stderr,"Error allocating memory\n");
        return;

    default:
    fprintf(stderr,"No error message was found\n");
        return ;
    }
}