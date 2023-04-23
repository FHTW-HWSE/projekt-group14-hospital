
#include "../include/definitions.h"

#ifndef CSV_WRITE_H
#define CSV_WRITE_H



/*
-Michi
Status: Finished 

*/




/**
 * @brief enum containing the error codes of the write CSV file
 */
enum CSV_WRITE_PD_ERRORS{
E_OPENING_CSV_FILE = 200,
E_CLOSING_CSV_FILE = 201,
E_CONVERTING_INT_TO_STRING = 202
};

/**
 * @brief enum containing the return values of the 
 */
enum CSV_WRITE_PD_RETURNS{
    CSV_WRITE_PD_EXECUTED_SUCCESSFULLY_AND_CRERATED_FILE = 2,
    CSV_WRITE_PD_EXECUTED_SUCCESSFULLY = 0,
    CSV_WRITE_PD_FALIED = -1

};



/**
 * @brief Function which writes a new entery into the Patient Data CSV file
 *
 * All Parameters until mode are the Patient data beeing written into the 
 * 
 * @param SocialSecurityNumber 
 * @param PatientName
 * @param ArrivalTime
 * @param DepartureTime
 * @param Infectious
 * @param seatingNumber
 * @param mode sets different extra modes in which the function can be executed //default functionality mode 0ch
 * @return int [0 if successfull normal write] [2 if a new csv file has been created] [-1 if an error occured]
 */


#define DEBUG_MESSAGES_WRITE_CSV 0 //set to 1 if you want to Print out Debug information

//michi, changed to int times
int writePatientData(unsigned int SocialSecurityNumber, char PatientName[MAX_PATIENT_NAME], long ArrivalDateTime ,
                    long DepartureDateTime,char Infectious, unsigned short int seatingNumber, short mode);



#endif
