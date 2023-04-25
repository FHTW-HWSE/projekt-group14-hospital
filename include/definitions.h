
//=========================================================================Michi 
#ifndef DEFINITIONS_H
#define DEFINITIONS_H



#define MAX_PATIENT_NAME 30
#define MAX_DATE_TIMESTRING_LENGTH 16
#define MAX_SOCIAL_SECURITY_NUMBER_LENGTH 10

//=========================================================================Valentina

#define MAP_ROWS 5
#define MAP_COLUMNS 5

enum ERROR_CODES
{
    ERR_OPENING_FILE = 4,
    ERR_MALLOC = 5,
    ERR_CLOSING_FILE = 6
};


typedef struct {
		unsigned long ssn;             // Social Security Number
		char name[MAX_PATIENT_NAME];   // Patient Name
		int arrivalTime;              // Arrival Time
		long arrivalDate;             // Arrival Date
		int departureTime;            // Departure Time
		long departureDate;           // Departure Date
		char infectious;              // Infectious[Y/N]
		int seatingNumber;            // Seating Number
		struct PatientRecord *next;
	} PatientRecord;

typedef struct{
    PatientRecord *prev;
    PatientRecord *data;
    PatientRecord *next;
} PatientList;

//_____End

#endif