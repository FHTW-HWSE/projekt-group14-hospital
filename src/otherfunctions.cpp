#include "../include/otherfunctions.h"

PatientRecord *findPatient(PatientList *head, unsigned long soz) {
    PatientList *patient = head;
    
    while(patient != NULL) {
        
        if(patient->data->ssn == soz) {
            return patient->data;
        }
        patient = patient->next;
    } 
    return NULL;
}