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
/**
 * @brief Creates a new linked list containing patients with seating numbers and no departure date.
 *
 * This function iterates through the given linked list of patients and creates a new linked list
 * that contains only the patients with seating numbers and no departure date.
 *
 * @param head The head of the original linked list of patients.
 * @return A new linked list containing patients with seating numbers and no departure date.
 */
PatientList* getWaitList(PatientList *head);

void freeAll(PatientList *prio, PatientList *wait, PatientList *patNeighbours, PatientRecord *pat, PatientRecord *tempPat);
/**
 * @brief Frees the memory allocated for a linked list of patients.
 *
 * This function frees the memory allocated for each node in the linked list of patients,
 * including the data stored in each node.
 *
 * @param head The head of the linked list of patients.
 */

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
/**
 * @brief Initializes the seating map with seat numbers and availability.
 *
 * This function initializes the seating map by assigning seat numbers
 * to each seat and setting their availability status to false.
 *
 * @param seatingMap The seating map array to be initialized.
 */
void initializeSeatingMap(Seat seatingMap[MAP_ROWS][MAP_COLUMNS]);
/**
 * @brief Reserves a seat by its seat number.
 *
 * This function reserves a seat in the seating map by searching for
 * the seat with the specified seat number. If the seat is available,
 * it is reserved (availability status set to true) and the function
 * returns true. If the seat is already reserved or the seat number
 * is not found, the function returns false.
 *
 * @param seatNumber The seat number of the seat to be reserved.
 * @param seatingMap The seating map array to search for the seat.
 * @return True if the seat was successfully reserved, false otherwise.
 */

bool reserveSeatByNumber(int seatNumber, Seat seatingMap[MAP_ROWS][MAP_COLUMNS]);
/**
 * @brief Cancels a seat reservation by its seat number.
 *
 * This function cancels the reservation of a seat in the seating map
 * by searching for the seat with the specified seat number. If the
 * seat is currently reserved, the reservation is canceled (availability
 * status set to false) and the function returns true. If the seat is
 * not currently reserved or the seat number is not found, the function
 * returns false.
 *
 * @param seatNumber The seat number of the seat to cancel the reservation.
 * @param seatingMap The seating map array to search for the seat.
 * @return True if the reservation was successfully canceled, false otherwise.
 */

bool cancelReservationByNumber(int seatNumber, Seat seatingMap[MAP_ROWS][MAP_COLUMNS]);
/**
 * @brief Prints out the seating map.
 *
 * This function prints out the seating map, displaying the seat numbers
 * and their reservation status. Reserved seats are marked with 'X', while
 * available seats are represented by their seat numbers. The seating map
 * is printed in a grid format.
 *
 * @param seatingMap The seating map array to print.
 */

void printOutMap(Seat seatingMap[MAP_ROWS][MAP_COLUMNS]);
/**
 * @brief Reserves seats from the patient list on the seating map.
 *
 * This function reserves seats on the seating map based on the seating numbers
 * specified in the patient list. It iterates through the patient list and for
 * each patient, checks if their seating number is valid and if their departure
 * date is not set. If the conditions are met, the corresponding seat on the
 * seating map is reserved using the reserveSeatByNumber function.
 *
 * @param patientList The patient list containing the seating numbers.
 * @param seatingMap The seating map array to reserve seats on.
 */

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
