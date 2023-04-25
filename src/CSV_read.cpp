#include <stdio.h>
#include <stdlib.h>
#include "../include/CSV_read.h"

// TO DO ZLATKO: definitions.h & änderung struct date & time in funktion beachten 


PatientRecord *csv_read() {
	//open file + error handling
	FILE *file = fopen("test.csv", "r");

	if (file == NULL) {
		printf("Error opening file.\n");
		return NULL;
	}

	// Declare a pointer to the head of the linked list
	PatientRecord *head = NULL;
	// read= "value-counter" for iteration through the csv file
	int read = 0;
	// read and store all information into the struct until eof
	do {
		//allocate memory for the list
		PatientRecord *newPatient = malloc(sizeof(PatientRecord));
		if (newPatient == NULL){
        printf("Error allocating memory");
        return NULL;
        }
        newPatient->next = NULL;

		read = fscanf(file, "%ld,%49[^,],%d,%ld,%d,%ld,%c,%d\n",
				&newPatient->ssn, newPatient->name, &newPatient->arrivalTime,
				&newPatient->arrivalDate, &newPatient->departureTime,
				&newPatient->departureDate, &newPatient->infectious,
				&newPatient->seatingNumber);

		// patient has 8 struct-elements, if read =8 store the following information to the next patient
		if (read == 8) {
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
		//if file format incorrect or eof error handling
		if (read != 8 && !feof(file)) {
			printf("File format incorrect.\n");
			return NULL;
		}
		//error handling file pointer
		if (ferror(file)) {
			printf("Error reading file.\n");
			return NULL;
		}

	} while (!feof(file));

	fclose(file);

	return head;
}
