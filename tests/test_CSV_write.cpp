// Testregion



#include <catch2/catch.hpp>
#include <cstdint>
#include <string.h>
#include "../include/definitions.h"
#include "../include/CSV_write.h"
/**
 * @brief Unit test for generate_Write_String function.
 */

TEST_CASE("Generate Write String Test", "[generate_Write_String]")
{
    // Define test data
    unsigned long ssn = 123456789;
    char name[MAX_PATIENT_NAME] = "John Doe";
    int arrivalTime = 10;
    long arrivalDate = 20230101;
    int departureTime = 15;
    long departureDate = 20230102;
    char infectious = 'N';
    int seatingNumber = 1;

    // Call the function
    char *writeString = generate_Write_String(ssn, name, arrivalTime, arrivalDate, departureTime, departureDate, infectious, seatingNumber);

    // Check the generated write string
    
   char *  expectedString = "123456789,John Doe,10,20230101,15,20230102,N,1\n";

fprintf(stdout,"Teststring: %s\n", writeString);
fprintf(stdout,"Expectedstring: %s\n", expectedString);

    REQUIRE(0 == strcmp(writeString, expectedString));
    

    // Free the allocated memory
    free(writeString);
}



#if 0 //if to 0 to disable test

// Test case written using the catch2 framework
TEST_CASE("Test writePatientData", "[writePatientData]") {
    // Test case 1
    SECTION("Test writePatientData with valid input") {
        // Arrange
        unsigned long SocialSecurityNumber = 123456789;
        char PatientName[MAX_PATIENT_NAME] = "Max Mustermann";
        int arrivalTime = 1234;
        long arrivalDate = 123456789;
        int departureTime = 1234;
        long departureDate = 123456789;
        char Infectious = 'Y';
        int seatingNumber = 1234;

        // Act
        int result = writePatientData(SocialSecurityNumber, PatientName, arrivalTime, arrivalDate, departureTime, departureDate, Infectious, seatingNumber);

        // Assert
        REQUIRE(result == CSV_WRITE_PD_EXECUTED_SUCCESSFULLY_AND_CRERATED_FILE);
    }

    // Test case 2
    SECTION("Test writePatientData with invalid input") {
        // Arrange
        unsigned long SocialSecurityNumber = 123456789;
        char PatientName[MAX_PATIENT_NAME] = "Max Mustermann";
        int arrivalTime = 1234;
        long arrivalDate = 123456789;
        int departureTime = 1234;
        long departureDate = 123456789;
        char Infectious = 'Y';
        int seatingNumber = 1234;

        // Act
        int result = writePatientData(SocialSecurityNumber, PatientName, arrivalTime, arrivalDate, departureTime, departureDate, Infectious, seatingNumber);

        // Assert
        REQUIRE(result == CSV_WRITE_PD_EXECUTED_SUCCESSFULLY_AND_CRERATED_FILE);
    }
}



#endif

