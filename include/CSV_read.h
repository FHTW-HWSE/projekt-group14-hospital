#include "../include/definitions.h"
#ifndef CSV_READ_H
#define CSV_READ_H

/**
 * @brief Reads a CSV file containing patient data and stores the data in a linked list of Patientrecords.
 *
 * @param HEAD A pointer to the head of the linked list.
 * @return  -1 on error.
 *          1 on sucess
 */
int csv_read(PatientList * HEAD);

/**
 * @brief Reads patient records from a buffer containing CSV data for the Unit Test.
 *
 * This function parses a buffer containing patient data in CSV format and creates a linked list of PatientList structures
 * with the extracted information.
 *
 * @param HEAD A pointer to the head of the linked list.
 * @param buffer The buffer containing the CSV data.
 * @return Returns 1 on success, -1 on failure.
 */

int csv_read_from_buffer(PatientList *HEAD, const char *buffer);


/**
 * @brief 
 * 
 * @param HEAD 
 */
void freeLinkedList(PatientList * HEAD);

//old fucntion - Michi
//void printList(PatientList * HEAD);

#endif