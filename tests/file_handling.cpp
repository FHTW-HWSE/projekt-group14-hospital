#include "../include/CSV_read.h"
#include "../include/CSV_write.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEACTIVATE_FILE_HANDLING_TEST 1

#if DEACTIVATE_FILE_HANDLING_TEST

int main(void) {

	// Define the data to be written to the file
	unsigned long SocialSecurityNumber = 1234;
	char PatientName[MAX_PATIENT_NAME] = "Max";
	int arrivalTime = 1345;
	long arrivalDate = 20230424;
	int departureTime = 1630;
	long departureDate = 20230424;
	char Infectious = 'N';
	unsigned short int seatingNumber = 5;

	// Write the data to the file
	int writeResult = writePatientData(SocialSecurityNumber, PatientName,
			arrivalTime, arrivalDate, departureTime, departureDate, Infectious,
			seatingNumber, 1);

	if (writeResult != CSV_WRITE_PD_FALIED) {
		printf("Error writing data to file.\n");
		return 1;
	}

	// Read the data from the file
	PatientRecord* Patient= csv_read();

	// Compare the data that was read from the file with the data that was written to it
	if (SocialSecurityNumber != Patient[0].ssn
			|| strcmp(PatientName, Patient[0].name) != 0
			|| arrivalTime != Patient[0].arrivalTime
			|| arrivalDate != Patient[0].arrivalDate
			|| departureTime != Patient[0].departureTime
			|| departureDate != Patient[0].departureDate
			|| Infectious != Patient[0].infectious
			|| seatingNumber != Patient[0].seatingNumber) {
		printf(
				"Error: The data read from the file does not match the data that was written to it.\n");
		return 1;
	}
	printf("The data read from the file does match the data that was written to it");
	return 0;
}


#endif