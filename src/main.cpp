#include <stdio.h>
#include <stdlib.h>
#include "../include/definitions.h"
#include "../include/CSV_read.h"
#include "../include/CSV_write.h"
#include "../include/dateFunctions.h"
#include "../include/otherfunctions.h"
#include <catch2/catch.hpp>
#include <string.h>
#include "../include/printFunctions.h"



#pragma region MAIN
int main(int argc, char *argv[])
{
    //Test find
    PatientList *HEAD = (PatientList *)malloc(sizeof(PatientList));
    PatientRecord *pat = (PatientRecord*) malloc(sizeof(PatientRecord));
    HEAD->next = NULL;
    csv_read(HEAD);
    pat = findPatient(HEAD, 97);
    printf("Name: %lu\nDepDate: %lu\nDepTime: %d\n", pat->ssn, pat->departureDate, pat->departureTime);
    addDeparture(HEAD, 97);
    printf("Name: %lu\nDepDate: %lu\nDepTime: %d\n", pat->ssn, pat->departureDate, pat->departureTime);
    return 0;
/*
#pragma region MichisMagicTestArea
#if 0


    PatientList * HEAD = (PatientList *)malloc(sizeof(PatientList));
HEAD->data = NULL;
HEAD->next = NULL;



    csv_read(HEAD);
    //printf("after csv_read\n");
   // printf("1: %p \n", HEAD);
    //printf("2: %p \n", HEAD->next);
   


short retPrint = printPatientList(HEAD, SHORT);
   printf("retPrint: %d\n", retPrint);

    //printf("after printList\n");
    freeLinkedList(HEAD);
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

#pragma region SEATING MAP
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
/*
#pragma endregion
   
    menu(seatingMap); //note: func.returns:1=user wants to close program/-1=too many wrong inputs from user

    return 0;
*/}

#pragma endregion MAIN




