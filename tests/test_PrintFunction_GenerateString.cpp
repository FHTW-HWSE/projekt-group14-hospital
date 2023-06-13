#include "../include/printFunctions.h"
#include <catch2/catch.hpp>
#include "../include/definitions.h"
#include <stdlib.h>
#include <string.h>

TEST_CASE("Test generate Print string", "[printString]") {
    
char buffer[100];

//allocate memory for a patient record
PatientRecord *patient = (PatientRecord *)malloc(sizeof(PatientRecord));



patient->ssn = 123456789;
strcpy(patient->name, "Max Mustermann");
patient->arrivalDate = 123456789;
patient->arrivalTime = 123456789;
patient->departureDate = 123456789;
patient->departureTime = 123456789;
patient->seatingNumber = 1;
patient->infectious = 'N';






    SECTION("Test generate print string with valid input") {
       
        REQUIRE(generatePatientString(patient, buffer, WHOLE) == 0);
        REQUIRE(strcmp(buffer, "123456789,Max Mustermann,123456789,123456789,123456789,123456789,N,1\n") == 0);
        REQUIRE(generatePatientString(patient, buffer, SHORT) == 0);
        REQUIRE(strcmp(buffer, "123456789,Max Mustermann,123456789\n") == 0);
    
    }

free(patient);

}