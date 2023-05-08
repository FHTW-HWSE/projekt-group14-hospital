#include "../include/otherfunctions.h"

PatientRecord *findPatient(PatientList *head, unsigned long soz) {
    PatientList *patient = head;
    printf("test");
    while(patient != NULL) {
        patient = patient->next;
        if(patient->data->ssn == soz) {
            return patient->data;
        }
    } 
    return NULL;
}