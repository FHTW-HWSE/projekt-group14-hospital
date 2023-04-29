#include "../include/changePatientInfo.h"
#include <stdio.h>
#include <stdlib.h>
#include "../include/CSV_read.h"
#include "../include/CSV_write.h"
#include <string.h>

// status VERY UNFINISHED
#pragma region deletePatientInfo

/*
int deletePatientInfo(unsigned long SocialSecurityNumber){
    //opening the file and checking if it exists
    #pragma region File Opening
    //Testing if Requested File existes, if not creating it
    FILE * TestFileOpen = fopen(PATH_TO_PATIENT_DATA_CSV_FILE, "r");
    //if file doesnt exist create it 
    if (TestFileOpen == NULL){
        #if DEBUG_MESSAGES_WRITE_CSV 
        printf("Status writing Patient Data: No existing database, databse was created at %s!\n",PATH_TO_PATIENT_DATA_CSV_FILE);
        #endif
        TestFileOpen = fopen(PATH_TO_PATIENT_DATA_CSV_FILE, "w");
        fclose(TestFileOpen);
    } else {
    fclose(TestFileOpen);
    }
    // Opening File Stream
    //r+ so can also read from the file if last entery is newling
    FILE *file = fopen(PATH_TO_PATIENT_DATA_CSV_FILE, "r+");
    // Error Handeling if file could not be opened
    if (file == NULL){
        fprintf(stderr,"\nERROR opening the CSV File\nError ID: %i\n", E_OPENING_CSV_FILE);
        return -1;
    }
    #pragma endregion File Opening

    //forrmatting the file so the enteries are allways stored in the same format
    #pragma region File Formatting
    //var for formatting function
    int lastChar;
    //check if the file is empty to skipp the following formatting code
    char test = getc(file);
    if (test == EOF){
        fseek(file, -1, SEEK_CUR);
        goto skippedFormating;
    } else {
        fseek(file, -1, SEEK_CUR);
    }
    //check if the file starts with a new line, if not add one
    lastChar = getc(file);
    if (lastChar != '\n'){
        fseek(file, 0, SEEK_SET);
        fprintf(file, "\n");
    } else {
        fseek(file, 0, SEEK_SET);
    }
    //check if the file ends with a new line, if not add one
    fseek(file, -1, SEEK_END);
    lastChar = getc(file);
    if (lastChar != '\n'){
        fseek(file, 0, SEEK_END);
        fprintf(file, "\n");
    } else {
        fseek(file, 0, SEEK_END);
    }

}
*/
#pragma endregion deletePatientInfo

//status: FINISHED, ..but untested
#pragma region changePatient Infectious Status

short changePatientInfectiousSSN(PatientList* HEAD, unsigned long PatientSSN, char NewInfectiousStatus){
    PatientList * current = HEAD;
    while (current != NULL){
        if (current->data->ssn == PatientSSN){
            current->data->infectious = NewInfectiousStatus;
            return RET_CHINF_SUCCESS;
        }
        current = current->next;
    }
    return RET_CHINF_NOCHANGEMADE;
}

short changePatientInfectiousName(PatientList* HEAD, char * PatientName, char NewInfectiousStatus){
    PatientList * current = HEAD;
    while (current != NULL){
        if (strcmp(current->data->name, PatientName) == 0){
            current->data->infectious = NewInfectiousStatus;
            return RET_CHINF_SUCCESS;
        }
        current = current->next;
    }
    return RET_CHINF_NOCHANGEMADE;
}



#pragma endregion changePatient Infectious Status

