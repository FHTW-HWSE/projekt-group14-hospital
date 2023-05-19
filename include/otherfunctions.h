#pragma once

#include "definitions.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

PatientRecord *findPatient(PatientList *head, unsigned long soz);

void addDeparture(PatientList *head, unsigned long soz);

void updateCSV(PatientList *head, unsigned long soz);

void initializeSeatingMap(Seat seatingMap[MAP_ROWS][MAP_COLUMNS]);

bool reserveSeatByNumber(int seatNumber, Seat seatingMap[MAP_ROWS][MAP_COLUMNS]);

bool cancelReservationByNumber(int seatNumber, Seat seatingMap[MAP_ROWS][MAP_COLUMNS]);

void printOutMap(Seat seatingMap[MAP_ROWS][MAP_COLUMNS]);
/**
 * @brief Displays a menu and handles user input.
 *
 * This function displays a menu with several options and waits for the user to input a single character to select an option.
 * Depending on the selected option, a corresponding function is called or an error message is displayed.
 * This function continues to display the menu until the user selects the "quit" option or an error occurs.
 *
 * @return 1 if the program should be closed, -1 if an error occurred.
 */
int menu(Seat seatingMap[MAP_ROWS][MAP_COLUMNS]);
/**
 * @brief The declaration of error messages
 *
 * Depending on enum error it prints out the correct error message
 *
 * @param check enum error code
 *
 * @return  string, containing the correct messages
 */
void printErrorMsg(int error_code);
int readInPatientData(int elementCount, char ** returnWord);
//_____End
