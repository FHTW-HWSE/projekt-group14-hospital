#pragma once

#include "definitions.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
* @brief Retrieves a list of patients who were seated near a specific patient.
* This function creates a new patient list containing the patients who were seated near the patient
* with the specified social security number (soz). The seating arrangement is divided into rows of 5 seats.
* The function checks for patients who were seated in the same row or adjacent rows as the specified patient.
* The new patient list is returned, containing the neighbors of the specified patient.
* @param head Pointer to the head of the patient list.
* @param soz Social security number of the patient to find neighbors for.
* @return Pointer to the head of the patient list containing the neighbors, or an empty list if no neighbors are found.
*/
PatientList* getSeatNeighbour(PatientList *head, unsigned long soz);

/**
* @brief Finds a patient with the specified social security number (soz).
* This function searches for a patient with the given social security number in the patient list.
* It returns a pointer to the patient record if found, or NULL if the patient is not found.
* @param head Pointer to the head of the patient list.
* @param soz Social security number of the patient to find.
* @return Pointer to the patient record if found, or NULL if the patient is not found.
*/
PatientRecord *findPatient(PatientList *head, unsigned long soz);

/**
* @brief Adds departure information for a patient and updates the CSV file.
* This function adds departure information for a patient with the specified social security number (soz).
* The departure date is set to the current date, and the departure time is set to the current time.
* After updating the departure information, the CSV file is updated with the new patient data.
* @param head Pointer to the head of the patient list.
* @param soz Social security number of the patient to update.
*/
void addDeparture(PatientList *head, unsigned long soz);


/**
* @brief Updates the CSV file with the patient data.
* This function updates the CSV file with the patient data stored in the patient list.
* It opens the CSV file in write mode, clears its contents, and then writes the new data.
* If the file cannot be opened, an error message is printed and the function returns.
* @param head Pointer to the head of the patient list.
*/
void updateCSV(PatientList *head);

/**
* @brief Updates the infectious status of the patients in the contact list and updates the CSV file.
* This function updates the infectious status of the patients in the contact list
* to indicate that they have been in contact with an infectious patient.
* The infectious status of the patients in the contact list is set to 'C' (contact).
* After updating the infectious status, the CSV file is updated with the new patient data.
* @param head Pointer to the head of the patient list.
* @param contact Pointer to the head of the contact list.
*/
void updateContact(PatientList *head, PatientList *contact);

/**
* @brief Updates the infectious status of a patient and updates the CSV file.
* This function updates the infectious status of a patient with the specified social security number (soz).
* If the patient's current infectious status is 'N' (not infectious), it is updated to 'Y' (infectious),
* and if the current infectious status is 'Y', it is updated to 'N'.
* After updating the infectious status, the CSV file is updated with the new patient data.
* @param head Pointer to the head of the patient list.
* @param soz Social security number of the patient to update.
*/
void updateInfection(PatientList *head, unsigned long soz);

/**
* @brief Retrieves a priority list of patients from the main patient list.
* This function creates a new patient list containing only the patients with seatingNumber -1
* and departureDate 0, indicating high priority patients.
* The new priority list is sorted based on arrival date and time.
* @param head Pointer to the head of the main patient list.
* @return Pointer to the head of the priority patient list, or NULL if there are no patients to prioritize.
*/
PatientList* getPrioList(PatientList *head);

PatientList* getWaitList(PatientList *head);

void free_list(PatientList *head);

#pragma region SORT functions
/**
* @brief Swaps the patient records between two nodes in the patient list.
* This function swaps the patient records between two nodes in the patient list.
* @param a Pointer to the first node.
* @param b Pointer to the second node.
*/
void swapPatients(PatientList* a, PatientList* b);

/**
* @brief Sorts the patient list based on arrival date and time.
* @param head Pointer to the head of the patient list.
*/
void sortPatients(PatientList* head);

/**
* @brief Compares two patient records based on arrival date and time.
* @param patient1 Pointer to the first patient record.
* @param patient2 Pointer to the second patient record.
* @return -1 if patient1 arrives before patient2, 1 if patient1 arrives after patient2, 0 if both patients arrive at the same date and time.
*/
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
