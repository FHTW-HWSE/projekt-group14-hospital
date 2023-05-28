#include "../include/printFunctions.h"
#include <string.h>
#include "../include/otherfunctions.h"
#include <time.h>
//michi



 
/// function to print the patient list
/// Returns the number of printed elemntsm, -1 if the list is empty, -2 if the suvfuntion failed to generate a patient string

//Helper functions
short generatePatientString(PatientRecord *patient, char * Buffer, short type) ;
void printSepparatorLine(int type,int symbol);


short printPatientList(PatientList *head, short type){

    //checks if the passed list is valid
    if(head->data == NULL ) {
        printErrorMsg(ERR_PRINTF_EMPTY_LIST);
        return -1;
    }
   

    //buffer to hold one printable line
    char charBuffer[100];

//printing the header message
#if PRINT_HEADER_AND_CLOSE_MESSAGE 
    printf( "\n == Patient Print ==\n\n");
    if(type == WHOLE){
    printf("SSN\t\t|Name\t\t\t\t|A-Time\t|A-Date\t\t|D-Time\t|D-Date\t\t|Inf\t|Seat.No.|\n");
    printSepparatorLine(type,1);
    }
    if(type == SHORT){
    printf("SSN\t\t|Name\t\t\t       |\n");
    printSepparatorLine(type, 1);
    }
#endif

//return value subfunction
short retSub;

    PatientList *patient = head;
    int i = 0;
    while(patient != NULL) {

//DEBUG
//printf("a\n");

//call a function which generates a patient String which will be printed to the console
      retSub = generatePatientString(patient->data, charBuffer, type);


//DEBUG
//printf("b\n");

//if the function returns -1 nothing was written to the buffer and the function will return -2
if (retSub == -1){
    printErrorMsg(ERR_PRINTF_GENERATING_PATIENT_STRING);
    return -2;
}else {
    printf("%s", charBuffer); //printing the patient string
    
    //setting the buffer back to 0
    charBuffer[0] = '\0';



        patient = patient->next;
        i++;
        printSepparatorLine(type,2);
}
    }

//printing the closing message
#if PRINT_HEADER_AND_CLOSE_MESSAGE 
    printf("\n == End Patient Print ==\n\n");
    #endif

    return i;

}




//HELPER FUNCTIONS


//function which generates a patient String which will be printed to the console
// returns a status int
// also uses the type variable to determine how much of the patient data will be printed
//NOte that the buffer is allways 100 chars long so i am not passing the length
short generatePatientString(PatientRecord *patient, char * Buffer, short type) {
    
   //setting Buffer 0 to \0 to be able to determine if nothing was written to it
   Buffer[0] = '\0';



#pragma region convert time


//formatting the time and date to a printable format without the time.h functions
// taking into account that the leading 0 is missing if the number is smaller than 10
// doing this manually because the time.h functions are not really working with our format(or i cant get them to work)


char arrivalTime[6] = {};
int arrivalTime_h = patient->arrivalTime / 100;
int arrivalTime_m = patient->arrivalTime % 100;
sprintf(arrivalTime, "%02i:%02i", arrivalTime_h, arrivalTime_m);

char arrivalDate[11];
int arrivalDate_y = patient->arrivalDate / 10000;
int arrivalDate_m = (patient->arrivalDate % 10000) / 100;
int arrivalDate_d = patient->arrivalDate % 100;
sprintf(arrivalDate, "%02i.%02i.%04i", arrivalDate_d, arrivalDate_m, arrivalDate_y);

char departureTime[6];
int departureTime_h = patient->departureTime / 100;
int departureTime_m = patient->departureTime % 100;
sprintf(departureTime, "%02i:%02i", departureTime_h, departureTime_m);

char departureDate[11];
int departureDate_y = patient->departureDate / 10000;
int departureDate_m = (patient->departureDate % 10000) / 100;
int departureDate_d = patient->departureDate % 100;
sprintf(departureDate, "%02i.%02i.%04i", departureDate_d, departureDate_m, departureDate_y);


#pragma endregion convert time
//Not checking the vlaues because they should be checked in the generating functions, avoiding redundant code

//formating the seating number
char seatingNumber[4];
if(patient->seatingNumber == -1) {
    sprintf(seatingNumber, "na");
}else {
    sprintf(seatingNumber, "%i", patient->seatingNumber);
}

    //if type is set to WHOLE all the data will be printed
    if(type == WHOLE) {
        sprintf(Buffer, "%-10lu\t|%-30s\t|%s\t|%s\t|%s\t|%s\t|%c\t|%-3s     |\n", patient->ssn, patient->name,arrivalTime,arrivalDate, \
       departureTime,departureDate,patient->infectious, seatingNumber);
    }

    //if type is set to SHORT only the first two collumns will be printed
    else if(type == SHORT) {
    sprintf(Buffer,"%-10lu\t|%-30s|\n",patient->ssn, patient->name);
    }

// return -1 if nothing was written to the buffer
    if(Buffer[0] == '\0') {
        return -1;
    }else {
        return 0;
    }
    
}

// type: SHORT or WHOLE
// symbol: 1 = =, 2 = -
void printSepparatorLine(int type, int symbol) {

    int noOfPrintedChars;
    if(type == WHOLE) {
        noOfPrintedChars = 114;
    }else if(type == SHORT) {
        noOfPrintedChars = 48;
    }
    
    for(int i = 0; i < noOfPrintedChars; i++) {
        if(symbol == 1){
        printf("=");
        }
        if(symbol == 2){
        printf("-");
        }
    }
    printf("\n");
    }
