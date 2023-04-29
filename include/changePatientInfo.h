
#pragma once   //only include this header once per compilation unit
#include "../include/definitions.h"

//i wrote two function to change the infectious status of a patient
//one function takes the SSN of the patient as an argument, the other one takes the name of the patient as an argument
// the functions work by parsing through the linked list and comparing the SSN or name of the patient to the argument,
//if one was found the infectious status is changed and the function returns 0
//!! they do not change anything in the csv file, only in the linked list !!


/// @brief return values for the changePatientInfectious functions
enum CHANGEPATIENTINFECTIOUSSTATUSRETURNVALUES{
    RET_CHINF_NOCHANGEMADE = -1,
    RET_CHINF_SUCCESS = 0
};

/**
 * @brief changes the infectious status of a patient with the given SSN
 * 
 * @param HEAD 
 * @param PatientSSN 
 * @param NewInfectiousStatus 
 * @return short 
 */
short changePatientInfectiousSSN(PatientList* HEAD, unsigned long PatientSSN, char NewInfectiousStatus);

/**
 * @brief changes the infectious status of a patient with the given name
 * 
 * @param HEAD  pointer to the head of the linked list
 * @param PatientName Name of the patient in the linked list
 * @param NewInfectiousStatus the new infectious status that you want to assign to the patient
 * @return short 
 */
short changePatientInfectiousName(PatientList* HEAD, char * PatientName, char NewInfectiousStatus);