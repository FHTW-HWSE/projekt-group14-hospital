#pragma once

#include "../include/definitions.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//format of date/time
//iso 8601: YYYY-MM-DDThh:mm:ss, fff

/**
 * @brief Calculates the time in the format hhmm as an integer.
 * @param timeInfo Pointer to a struct tm containing the time information.
 * @return The time in the format hhmm as an integer, or -1 if timeInfo is a null pointer.
 */
int getTime();

/**
* @brief Retrieves the current date as a long value.
* This function obtains the current date by accessing the system time.
* It returns the date in the format yyyymmdd as a long value.
* @return The current date in the format yyyymmdd.
*/
long getDate();

/**
* @brief Searches for a patient with the specified social security number in a CSV file.
* Opens the CSV file and searches for a patient record with the matching social security number (ssn).
* Returns a pointer to the patient record if found, or NULL otherwise.
* @param ssn Social security number of the patient to search for.
* @return Pointer to the patient record if found, or NULL otherwise.
*/
PatientRecord* searchPatientInCSV(unsigned long ssn);

/*
time_t convertStringToDatetime(char * text);
char * convertDatetimeToString(time_t timestamp);*/