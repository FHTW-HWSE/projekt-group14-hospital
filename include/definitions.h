
//=========================================================================Michi 
#ifndef DEFINITIONS_H
#define DEFINITIONS_H
#include <stdbool.h>


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
    ERR_CLOSING_FILE = 6,
	ERR_GENERATING_PATIENT_STRING_PRINTFUNCTION = 7,
	ERR_EMPTY_LIST_PRINTFUNCTION = 8
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
	} PatientRecord;


typedef struct PatientList{
    PatientList *next;
    PatientRecord *data;
} PatientList;

typedef struct Seat {
    int seatNumber;
    bool isReserved;
} Seat;


#endif