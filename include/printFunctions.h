
#pragma once

#include "definitions.h"
#include <stdlib.h>
#include <stdio.h>

//definitions 
#define WHOLE 1 // if this is as type in the print patient list function all the collums will be printed
#define SHORT 2 // if this is set ype in the print patient list only the first thee collumns will be printed

#define PRINT_HEADER_AND_CLOSE_MESSAGE 1 //set this to 1 if you want to print out a header and a closing message

short printPatientList(PatientList *head, short type);


