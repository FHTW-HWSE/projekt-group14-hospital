#include "../include/definitions.h"
#ifndef CSV_READ_H
#define CSV_READ_H

/**
 * @brief Reads the contents of a CSV file into linked list of patients
 *
 * @return head pointer of patients list, NULL if  error
 */


// TO DO ZLATKO: definitions.h & änderung struct date & time in funktion beachten + 
// struct PatientRecord hier löschen & verkettete liste beachten
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