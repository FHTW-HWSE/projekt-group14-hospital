#include <stdio.h>
#include <stdlib.h>
#include "../include/CSV_read.h"
#include "../include/CSV_write.h"
#include "../include/dateFunctions.h"
#include <catch2/catch.hpp>

#define MAX_NAME_LENGTH 50

enum ERROR_CODES
{
    ERR_OPENING_FILE = 4,
    ERR_MALLOC = 5,
    ERR_CLOSING_FILE = 6
};

/*
typedef struct {
  int ssn;                      // Social Security Number
  char name[MAX_NAME_LENGTH];   // Patient Name
  int arrival_time;             // Arrival Time
  int departure_time;           // Departure Time
  char infectious;              // Infectious[Y/N]
  int seating_number;           // Seating Number
} PatientRecord;
 */

int menu();
const char *printErrorMsg(int error_code);

int main(int argc, char *argv[])
{

/*------------test für time-----------------*/
    int myTime = 0;
    time_t now;
    struct tm *timeInfo;

    time(&now);
    timeInfo = localtime(&now);

    myTime = getTime(timeInfo);
    printf("\n ---- Test für time fkt (to be deleted!)\n %d \n ---- end test time\n",myTime);
/*-----------------------------*/
   
    char *buffer = (char *)malloc(sizeof(char) * 1000);
    if (buffer == NULL){
       fprintf(stderr, "%s", printErrorMsg(ERR_MALLOC));
       return 1;
    }

    /* TODO new functions... 
    buffer = read_csv("test.csv"); 
    printf("%s", buffer);
    */


    menu(); //note: func.returns:1=user wants to close program/-1=too many wrong inputs from user
    free(buffer);

    return 0;
}

/**
 * @brief Displays a menu and handles user input.
 *
 * This function displays a menu with several options and waits for the user to input a single character to select an option.
 * Depending on the selected option, a corresponding function is called or an error message is displayed.
 * This function continues to display the menu until the user selects the "quit" option or an error occurs.
 *
 * @return 1 if the program should be closed, -1 if an error occurred.
 */
int menu() {
    int static check_default = 0;

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
                check_default++;
                if (check_default > 10) {
                    printf("Your input could not be processed for the %dth time...\n"
                           "closing program, bye!!!\n\n\n", check_default);
                    return -1;
                }
                printf("Your input could not be processed! Please enter only one character\n\n");
                continue;
        }
    }
}
/**
 * @brief The declaration of error messages
 *
 * Depending on enum error it prints out the correct error message
 *
 * @param check enum error code
 *
 * @return  string, containing the correct messages
 */
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