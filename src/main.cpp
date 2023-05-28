#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <catch2/catch.hpp>
#include "../include/definitions.h"
#include "../include/CSV_read.h"
#include "../include/CSV_write.h"
#include "../include/dateFunctions.h"
#include "../include/otherfunctions.h"
#include "../include/printFunctions.h"


#pragma region MAIN
int main(int argc, char *argv[]) {

//////////////////////////////////////
#pragma region MichisMagicTestArea

#if 0

//hall0
    PatientList * HEAD2 = (PatientList *)malloc(sizeof(PatientList));
HEAD2->data = NULL;
HEAD2->next = NULL;



    csv_read(HEAD2);
    //printf("after csv_read\n");
   // printf("1: %p \n", HEAD2);
    //printf("2: %p \n", HEAD2->next);
   


short retPrint = printPatientList(HEAD2, WHOLE);
   printf("retPrint: %d\n", retPrint);

    //printf("after printList\n");
    freeLinkedList(HEAD2);
    //printf("after freeLinkedList\n");
    return 23;
#endif

#if 0
writePatientData(123456, "Michi", 0340,20345555, 1234, 654321, 'n', -1);
writePatientData(123456, "Fritz", 0340,20345555, 1234, 654321, 'n', -1);
writePatientData(123456, "Fred", 0340,20345555, 1234, 654321, 'n', -1);
return 10;
#endif


#pragma endregion MichisMagicTestArea
//////////////////////////////////////

//////////////////////////////////////
#pragma region EmilsMagicTestArea

#if 0
    //Test find and Departure Time/Date
    //Test infection change
    //Test prio list
    PatientList *HEAD = (PatientList *)malloc(sizeof(PatientList));
    PatientRecord *pat = (PatientRecord*) malloc(sizeof(PatientRecord));
    HEAD->data = NULL;
    HEAD->next = NULL;
    csv_read(HEAD);
    PatientList *prio = (PatientList *)malloc(sizeof(PatientList));
    prio = getSeatNeighbour(HEAD, 98765499);
    printPatientList(prio, WHOLE);
    return 0;
    //printf("Name: %lu\nDepDate: %lu\nDepTime: %d\nInfection: %c\n---neu---\n", pat->ssn, pat->departureDate, pat->departureTime, pat->infectious);
    //addDeparture(HEAD, 97);
    //updateInfection(HEAD, 97);
    //printf("Name: %lu\nDepDate: %lu\nDepTime: %d\nInfection: %c\n", pat->ssn, pat->departureDate, pat->departureTime, pat->infectious);
/*
    PatientList *prio = (PatientList *)malloc(sizeof(PatientList));
    prio = getPrioList(HEAD);
    printPatientList(prio, WHOLE);
    return 0;
*/

#endif

#pragma endregion EmilsMagicTestArea
//////////////////////////////////////

//////////////////////////////////////
#pragma region ZlatkosMagicTestArea

#if 0
    PatientList *HEAD = (PatientList *)malloc(sizeof(PatientList));
    PatientRecord *pat = (PatientRecord*) malloc(sizeof(PatientRecord));
    HEAD->data = NULL;
    HEAD->next = NULL;
    csv_read(HEAD);   
    PatientList *wait = (PatientList *)malloc(sizeof(PatientList));
    wait = getWaitList(HEAD);
    printPatientList(wait,WHOLE);
    return 0;


#endif

#pragma endregion ZlatkosMagicTestArea
//////////////////////////////////////

//////////////////////////////////////
#pragma region SEATING MAP
#if 0
   //Initalize seating map
    Seat seatingMap[MAP_ROWS][MAP_COLUMNS];
    initializeSeatingMap(seatingMap);
    /*
    int num = 1;
    for (int i = 0; i < MAP_ROWS; i++) {
        for (int j = 0; j < MAP_COLUMNS; j++) {
            seatingMap[i][j] = num;
            num++;
        }
    }
*/
    //seatingMap[2][3] = 0;
    //printOutMap(seatingMap);

#endif
#pragma endregion
//////////////////////////////////////

//////////////////////////////////////
#pragma region REAL MAIN
#if 1

    Seat seatingMap[MAP_ROWS][MAP_COLUMNS];
    initializeSeatingMap(seatingMap);
   
    PatientList *HEAD = (PatientList *)malloc(sizeof(PatientList));

    HEAD->data = NULL;
    HEAD->next = NULL;
    csv_read(HEAD);
    reserveSeatsFromPatientList(HEAD, seatingMap);
    menu(seatingMap, HEAD); //note: func.returns:1=user wants to close program/-1=too many wrong inputs from user

#endif
#pragma endregion
//////////////////////////////////////

    return 0;
}
#pragma endregion MAIN