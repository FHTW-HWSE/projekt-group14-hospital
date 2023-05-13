#include "../include/printFunctions.h"


//michi
//The functions in this file are beeing written with test driven development in mind

 
/// function to print the patient list
/// Returns the number of printed elemntsm, -1 if the list is empty, -2 if the suvfuntion failed to generate a patient string

//Helper function
short generatePatientString(PatientRecord *patient, char * Buffer, short type) ;

short printPatientList(PatientList *head, short type){

    //checks if the passed list is valid
    if(head == NULL || head->data == NULL) {
        return -1;
    }
   

    //buffer to hold one printable line
    char charBuffer[100];

//printing the header message
#if PRINT_HEADER_AND_CLOSE_MESSAGE 
    printf( "\n == Complete Patient list ==\n\n");
#endif

//return value subfunction
short retSub;

    PatientList *patient = head;
    int i = 0;
    while(patient != NULL) {

//call a function which generates a patient String which will be printed to the console
      retSub = generatePatientString(patient->data, charBuffer, type);
//if the function returns -1 nothing was written to the buffer and the function will return -2
if (retSub == -1)
{
    fprintf(stderr, "Error: Failed to generate patient string\n EID = %S", ERR_GENERATING_PATIENT_STRING_PRINTFUNCTION );
    return -2;
}else {
    printf("%s", charBuffer); //printing the patient string
    //setting the buffer back to 0
    charBuffer[0] = '\0';


        patient = patient->next;
        i++;
}
    }

    return i;


//printing the closing message
#if PRINT_HEADER_AND_CLOSE_MESSAGE 
    printf("\n == End of Patient list ==\n\n");
    #endif

}


//HELPER FUNCTIONS


//function which generates a patient String which will be printed to the console
// returns a status int
// also uses the type variable to determine how much of the patient data will be printed
//NOte that the buffer is allways 100 chars long so i am not passing the length
short generatePatientString(PatientRecord *patient, char * Buffer, short type) {
    
   //setting Buffer 0 to \0 to be able to determine if nothing was written to it
   Buffer[0] = '\0';

//Not checking the vlaues because they should be checked in the generating functions, avoiding redundant code

    //if type is set to WHOLE all the data will be printed
    if(type == WHOLE) {
        sprintf(Buffer, "%lu\t%s\t%i\t%i\t%i\t%i\t%c\t%i\n", patient->ssn, patient->name, patient->arrivalTime, patient->arrivalDate, \
       patient->departureTime, patient->departureDate,patient->infectious, patient->seatingNumber);
    }

    //if type is set to SHORT only the first two collumns will be printed
    else if(type == SHORT) {
        sprintf(Buffer,"%lu\t%s\n",patient->ssn, patient->name);
    }

// return -1 if nothing was written to the buffer
    if(Buffer[0] == '\0') {
        return -1;
    }else {
        return 0;
    }

}

