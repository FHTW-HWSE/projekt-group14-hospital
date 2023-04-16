#ifndef CSV_WRITE_H
#define CSV_WRITE_H

#define MAX_PATIENT_NAME 30
#define MAX_TIMESTRING_LENGTH 6

/*
-Michi
Status: Unfinished
Working on the writePatient Data Function
*/


/**
 * @brief enum containing the error codes of the write CSV file
 */
enum CSV_WRITE_ERRORS{
E_OPENING_CSV_FILE = 200,
E_CLOSING_CSV_FILE = 201
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

int writePatientData(unsigned int SocialSecurityNumber, char PatientName[MAX_PATIENT_NAME], char ArrivalTime[MAX_TIMESTRING_LENGTH],
                    char DepartureTime[MAX_TIMESTRING_LENGTH],char Infectious, unsigned short int seatingNumber);



#endif
