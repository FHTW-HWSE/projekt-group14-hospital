#ifndef CSV_WRITE_H
#define CSV_WRITE_H
#include "CSV_write.h"

#define MAX_PATIENT_NAME 30
#define MAX_TIMESTRING_LENGTH 10

/*
-Michi
Status: Finished but needs to be expanded
Testing: Mostly done but still more needed

*/


/**
 * @brief enum containing the error codes of the write CSV file
 */
enum CSV_WRITE_ERRORS{
E_OPENING_CSV_FILE = 200,
E_CLOSING_CSV_FILE = 201,
E_CONVERTING_INT_TO_STRING = 202
};

/**
 * @brief Function which writes a new entery into the Patient Data CSV file
 *
 * @param SocialSecurityNumber
 * @param PatientName
 * @param ArrivalTime
 * @param DepartureTime
 * @param Infectious
 * @param seatingNumber
 * @return int [0 if successfull normal write] [2 if a new csv file has been created] [-1 if an error occured]
 */

//michi, changed to int times
int writePatientData(unsigned int SocialSecurityNumber, char PatientName[MAX_PATIENT_NAME], int ArrivalTime,
                    int DepartureTime,char Infectious, unsigned short int seatingNumber);



#endif
