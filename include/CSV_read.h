#include "../include/definitions.h"
#ifndef CSV_READ_H
#define CSV_READ_H

/**
 * @brief Reads a CSV file containing patient data and stores the data in a linked list.
 *
 * @param HEAD A pointer to the head of the linked list.
 * @return The number of successfully read patient records or -1 on error.
 */
int csv_read(PatientList * HEAD);


/**
 * @brief 
 * 
 * @param HEAD 
 */
void freeLinkedList(PatientList * HEAD);

//old fucntion - Michi
//void printList(PatientList * HEAD);

#endif