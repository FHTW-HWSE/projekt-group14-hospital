#pragma once

#include "definitions.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

PatientList* getSeatNeighbour(PatientList *head, unsigned long soz);

PatientRecord *findPatient(PatientList *head, unsigned long soz);

void addDeparture(PatientList *head, unsigned long soz);

void updateCSV(PatientList *head);

void updateInfection(PatientList *head, unsigned long soz);

PatientList* getPrioList(PatientList *head);

PatientList* getWaitList(PatientList *head);

void free_list(PatientList *head);

#pragma region SORT functions 
void swapPatients(PatientList* a, PatientList* b);
void sortPatients(PatientList* head);
int compare(PatientRecord* patient1, PatientRecord* patient2);

#pragma endregion

#pragma region SEATING-MAP
void initializeSeatingMap(Seat seatingMap[MAP_ROWS][MAP_COLUMNS]);

bool reserveSeatByNumber(int seatNumber, Seat seatingMap[MAP_ROWS][MAP_COLUMNS]);

bool cancelReservationByNumber(int seatNumber, Seat seatingMap[MAP_ROWS][MAP_COLUMNS]);

void printOutMap(Seat seatingMap[MAP_ROWS][MAP_COLUMNS]);

void reserveSeatsFromPatientList(PatientList* patientList, Seat seatingMap[MAP_ROWS][MAP_COLUMNS]);

#pragma endregion

#pragma region ADD NEW PATIENT functions

/**
 * @brief Checks if a given string is a valid social security number.
 *
 * @param str The string to check.
 * @return true if the string is a valid social security number, otherwise false.
 */
bool isValidSSN(const char *str);

/**
 * @brief Checks if a given string consists only of numeric characters.
 *
 * @param str The string to check.
 * @return true if the string consists only of numeric characters, otherwise false.
 */
bool isNumericInput(const char *str);

/**
 * @brief Converts a given string to a social security number.
 *
 * @param str The string to convert.
 * @return The converted social security number as unsigned long. Returns 0 for invalid input.
 */
unsigned long convertSSN(const char *str);

/**
 * @brief Gets the social security number from the user.
 *
 * @return The social security number entered by the user as an unsigned long.
 *         Returns 0 if the input is invalid or too many invalid attempts are made.
 */
unsigned long getSSNfromUser();

/**
 * @brief Enters the patient's name.
 *
 * @param patient Pointer to the PatientRecord structure to store the patient's name.
 */
void enterPatientName(PatientRecord *patient);

/**
 * @brief Enters the infectious status of the patient.
 *
 * @param patient Pointer to the PatientRecord structure to store the infectious status.
 * @return true if the infectious status is successfully entered, false if too many invalid attempts are made.
 */
bool enterInfectiousStatus(PatientRecord *patient);

/**
 * @brief Selects the seating number for the patient.
 *
 * @param seatingMap The seating map for available seats.
 * @return The selected seating number if a valid number is entered, -1 if too many invalid attempts are made.
 */
int selectSeatingNumber(Seat seatingMap[MAP_ROWS][MAP_COLUMNS]);

/**
 * @brief Enters the mode of arrival for the patient.
 *
 * @param patient Pointer to the PatientRecord structure to store the mode of arrival.
 * @param seatingMap The seating map for available seats.
 * @return true if the mode of arrival is successfully entered, false if too many invalid attempts are made.
 */
bool enterModeOfArrival(PatientRecord *patient, Seat seatingMap[MAP_ROWS][MAP_COLUMNS]);

/**
 * @brief Adds a new patient to the system.
 *
 * @param seatingMap The seating map for available seats.
 * @return 0 if the patient is successfully added, 1 if there is an error or too many invalid attempts are made.
 */
int addNewPatient(Seat seatingMap[MAP_ROWS][MAP_COLUMNS]);

#pragma endregion




/**
 * @brief Displays a menu and handles user input.
 *
 * This function displays a menu with several options and waits for the user to input a single character to select an option.
 * Depending on the selected option, a corresponding function is called or an error message is displayed.
 * This function continues to display the menu until the user selects the "quit" option or an error occurs.
 *
 * @return 1 if the program should be closed, -1 if an error occurred.
 */
int menu(Seat seatingMap[MAP_ROWS][MAP_COLUMNS], PatientList *head);
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
