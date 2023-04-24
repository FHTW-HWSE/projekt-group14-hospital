#include <stdio.h>
#include <stdlib.h>
//#include "../include/CSV_read.h"
#include "../include/CSV_write.h"
#include "../include/dateFunctions.h"
#include "../include/definitions.h"
#include <catch2/catch.hpp>
#include <string.h>


void printOutMap(int (*seatingMap)[MAP_ROWS]);
int menu();
const char *printErrorMsg(int error_code);
 int readInPatientData(int elementCount, char ** returnWord);

int main(int argc, char *argv[])
{

/*
// Test Writefunction Michi
writePatientData(
    1234567890,
    "Abed",
    1236,
    12345677,
    1234,
    12345676,
    'Y',
    123,
    0
    );
return 0;
*/



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



//TO DO 
int addNewPatient(){

//initialize patient struct to save data which will be passed to the writePatientData function
//All the data will be temporarily saved in the struct and then passed to the writePatientData function
    PatientRecord tempPatient = {0, "", 0, 0, 0, 0, 'N', 0};

    int checkDefault = 0;
    printf("Please enter the patients social security number (FORMAT: 0000YYMMDD)\n");


/*  completely fucked -michi
char temChar[12] = "0000000000";
    char* tempCharAdress[MAX_SOCIAL_SECURITY_NUMBER_LENGTH+2] = &temChar;
   
readInPatientData(MAX_SOCIAL_SECURITY_NUMBER_LENGTH, tempCharAdress);
sscanf(*tempCharAdress, "%lu", tempPatient.ssn);
//debug prinf tempSSNcharSSNchar
printf("tempSSNchar: %s", *tempCharAdress);
//debug printf of the patients ssn
printf("SSN: %lu", tempPatient.ssn);l

*/



   //general function for reading in of the patient data into the struct in the same way as above
   //int readPatientDataInput(PatientRecord *tempPatient, char *tempSSNchar, int checkDefault){

    
    printf("\nPlease enter the patients name (FORMAT: Surname Forename)\n");

    printf("\nPlease press 'a' if the patient came by ambluance or 'o' if they came by themself\n");
     while (1) {
        int c = getchar();
            if (getchar() != '\n') {
                while (getchar() != '\n'); // to catch all characters if user enters too many
            }
        switch (c){

        /***patient came by ambulance***/
        case 'a': 
            printf("Patient by ambulance TBD\n");

            
            //TO DO Set seatingNumber to -1
            //TO DO Set infectious to N
            return 0;
        /***patient came by themself***/
        case 'o':
            printf("Patient by themself TBD\n");
            //TO DO getTime & Date + save
            //TO DO ask if infectous
            //TO DO ask seating number
            return 0;
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
    }

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


