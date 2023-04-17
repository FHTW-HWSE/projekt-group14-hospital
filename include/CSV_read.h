#ifndef CSV_READ_H
#define CSV_READ_H

#define MAX_NAME_LENGTH 50
#define MAX_PATIENT_SIZE 1000
/**
 * @brief Reads the contents of a CSV file into structs of patients
 *
 * @return structs of patients, 0 successful, 1 error
 */

typedef struct {
		int ssn;                      // Social Security Number
		char name[MAX_NAME_LENGTH];   // Patient Name
		char arrival_time[6];             // Arrival Time
		char departure_time[6];           // Departure Time
		char infectious;              // Infectious[Y/N]
		int seating_number;           // Seating Number
	} PatientRecord;

int csv_read();
#endif