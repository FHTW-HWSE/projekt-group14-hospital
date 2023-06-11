#include <stdio.h>
#include <stdlib.h>
#include "../include/CSV_read.h"
#include "../include/otherfunctions.h"
#include "../include/definitions.h"

// TO DO ZLATKO: definitions.h & änderung struct date & time in funktion beachten 


int csv_read(PatientList * HEAD) {
	//open file + error handling
	FILE *file = fopen("../programFiles/PatientData/PatientDataDB.csv", "r"); //Startpoint "src/"

	if (file == NULL) {
		printErrorMsg(ERR_OPENING_FILE);
		return -1;
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
        	printErrorMsg(ERR_MALLOC);
        	return -1;
        }


		PatientList * listElement;
		//allocate Memory for the PatientList
		if (HEAD->data != NULL){
		 	listElement = (PatientList *)malloc(sizeof(PatientList));
			if (listElement == NULL){
        		printErrorMsg(ERR_MALLOC);
        		return -1;
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

		//error handling file pointer
		if (ferror(file)) {
			printf("Error reading file.\n");
			return -1;
		}

	} while (!feof(file));

	fclose(file);

// Function finished successfully
	return 1;
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



