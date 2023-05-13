#include <stdio.h>
#include <stdlib.h>
#include "../include/CSV_read.h"

// TO DO ZLATKO: definitions.h & änderung struct date & time in funktion beachten 


int csv_read(PatientList * HEAD) {
	//open file + error handling
	FILE *file = fopen("../programFiles/PatientData/PatientDataDB.csv", "r");

	if (file == NULL) {
		printf("Error opening file.\n");
		return NULL;
	}


	// read= "value-counter" for iteration through the csv file
	int read = 0;
	// read and store all information into the struct until eof

	//last written element for linked list
	PatientList * lastElement = NULL;
	do {


	

		//allocate memory for the list
		PatientRecord *newPatient = (PatientRecord*)malloc(sizeof(PatientRecord));
		if (newPatient == NULL){
        printf("Error allocating memory");
        return NULL;
        }


PatientList * listElement;
	//allocate Memory for the PatientList
	if (HEAD->data != NULL){
		 listElement = (PatientList *)malloc(sizeof(PatientList));
		if (listElement == NULL){
        printf("Error allocating memory");
        return NULL;
        }
	}

//REWRITTEN SO FIRST ELEMENT IS HEAD
			//IF first element case
			if (HEAD->data == NULL){
				//HEAD->next = listElement;
				HEAD->data = newPatient;
			lastElement = HEAD;	
			// skip the creation of a new list element by jupting over the following code
			goto skip;
			}

	//following element case
			if (HEAD->data != NULL){
				lastElement->next = listElement;
				listElement->next =NULL;
				listElement->data = newPatient;
				lastElement = listElement;
			}


// So data is only written to the first element in the first cycle
skip:
		
			

       

		read = fscanf(file, "%ld,%49[^,],%d,%ld,%d,%ld,%c,%d\n",
				&newPatient->ssn, newPatient->name, &newPatient->arrivalTime,
				&newPatient->arrivalDate, &newPatient->departureTime,
				&newPatient->departureDate, &newPatient->infectious,
				&newPatient->seatingNumber);


/*
		// patient has 8 struct-elements, if read =8 store the following information to the next patient
		if (read == 8) {
			 Alt von Zlatko
			// Add the new patient to the end of the linked list
			if (head == NULL) {
				head = newPatient;
			} else {
				PatientRecord *current = head;
				while (current->next != NULL) {
					current = current->next;
				}
				current->next = newPatient;
				
			}
			
		}

		*/

	/*
	Alt Zlatko
		//if file format incorrect or eof error handling
		if (read != 8 && !feof(file)) {
			printf("File format incorrect.\n");
			return NULL;
		}
		*/
		//error handling file pointer
		if (ferror(file)) {
			printf("Error reading file.\n");
			return NULL;
		}

	} while (!feof(file));

	fclose(file);

	return 4;
}

//function which frees all the memory allocated for the linked list and 
void freeLinkedList(PatientList * HEAD){
	//free all the memory for the linked list and its data elements in a loop
	PatientList * tempElement = HEAD;
	PatientList * tempFreeElement;
	while (tempElement->next != NULL){
		free(tempElement->data);
		tempFreeElement = tempElement;
		tempElement = tempElement->next;
		free(tempFreeElement);
	}
}


/*

Michi, old but works, replaced with new function

//function to print the linked list
void printList(PatientList * HEAD){
		PatientList * tempElement = HEAD;
	while (tempElement->next != NULL){
		tempElement = tempElement->next;

		 printf("Patient Record:\n"
       "SSN: %lu\n"
       "Name: %s\n"
       "Arrival Time: %d\n"
       "Arrival Date: %ld\n"
       "Departure Time: %d\n"
       "Departure Date: %ld\n"
       "Infectious: %c\n"
       "Seating Number: %d\n\n\n",
       tempElement->data->ssn, tempElement->data->name, tempElement->data->arrivalTime, tempElement->data->arrivalDate,
       tempElement->data->departureTime, tempElement->data->departureDate, tempElement->data->infectious, tempElement->data->seatingNumber);

	
	}
}

*/
