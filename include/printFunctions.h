
#pragma once

#include "definitions.h"
#include <stdlib.h>
#include <stdio.h>


//Tests:
// Pritheader and closing message definition works PASSED
// printPatientList returns -1 if the list is empty PASSED
// printPatientList returns the correct number of printed patients PASSED
// printPatientList returns -2 if the subfunction failed to generate a patient string PASSED

//Further Tests in the test_PrintFunction_GenerateString.cpp file

//definitions 
//Types that can be passed to the printPatientList function
#define WHOLE 1 // if this is as type in the print patient list function all the collums will be printed
#define SHORT 2 // if this is set ype in the print patient list only the first thee collumns will be printed

#define PRINT_HEADER_AND_CLOSE_MESSAGE 1 //set this to 1 if you want to print out a header and a closing message

/**
 * @brief function to print the patient list
 * 
 * note that when firstly allocating the head pointer the next and data 
 * 
 * @param head Pass the allocated head of the list, adapted to correct linked list version ;) @emil 
 * @param type Pass the type of the print, either WHOLE or SHORT changes the look of the output
 * @return short 
 *      -1 if the list is empty
 *      -2 if the subfunction failed to generate a patient string
 */
short printPatientList(PatientList *head, short type);

//Helper function, only here for Testframework
short generatePatientString(PatientRecord *patient, char * Buffer, short type) ;

