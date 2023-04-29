


#ifndef CSV_WRITE_H
#define CSV_WRITE_H

#include "../include/definitions.h"

extern const char* PATH_TO_PATIENT_DATA_CSV_FILE;
/*
-Michi
Status: Finished 
*/

#pragma region enums
/**
 * @brief enum containing the error codes of the write CSV file
 *        only for the error codes 
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
#pragma endregion enums
/**
 * @brief Function which writes a new entery into the Patient Data CSV file
 *
 * All Parameters until mode are the Patient data beeing written into the 
 * 
 * @param SocialSecurityNumber Social Security Number of the Patient
 * @param PatientName Name of the Patient
 * @param arrivalTime Time of arrival of the Patient
 * @param arrivalDate Date of arrival of the Patient
 * @param departureTime Time of departure of the Patient
 * @param departureDate Date of departure of the Patient
 * @param Infectious Infectiousness of the Patient
 * @param seatingNumber Seating Number of the Patient
 * @return see enum CSV_WRITE_PD_RETURNS
 */


#define DEBUG_MESSAGES_WRITE_CSV 0 //set to 1 if you want to Print out Debug information


//michi, changed to int times
int writePatientData(unsigned long SocialSecurityNumber, char PatientName[MAX_PATIENT_NAME], int arrivalTime, long arrivalDate,
                    int departureTime,long departureDate,char Infectious,int seatingNumber);


// ################### M_WRITEPATIENTDATASTRUCT  ###################
// Macro to help you write to the CSV file using a Struct
// just write the macro and the PATIENT struct pointer into your code and it will write the data from the Struct
#define M_WRITEPATIENTDATASTRUCT(patientStruct)  writePatientData(patientStruct->ssn, patientStruct->name, patientStruct->arrivalTime, patientStruct->arrivalDate, \
       patientStruct->departureTime, patientStruct->departureDate,patientStruct->infectious, patientStruct->seatingNumber);

// ################### M_WRITEPATIENTDATANODE ###################
// same as above but with a node istead of a struct
#define M_WRITEPATIENTDATANODE(patientNode)  writePatientData(patientNode->data->ssn,patientNode->data->name,patientNode->data->arrivalTime,\
patientNode->data->arrivalDate,patientNode->data->departureTime,patientNode->data->departureDate,patientNode->data->infectious,patientNode->data->seatingNumber);

#endif
