// Testregion



#include <catch2/catch.hpp>
#include <cstdint>
#include <string.h>
#include "../include/definitions.h"
#include "../include/CSV_write.h"


TEST_CASE("Write Patient Data Test", "[writePatientData]") {
    // Generate test data
    unsigned long ssn = 123456789;
    char name[MAX_PATIENT_NAME] = "John Doe";
    int arrivalTime = 10;
    long arrivalDate = 20230101;
    int departureTime = 15;
    long departureDate = 20230102;
    char infectious = 'N';
    int seatingNumber = 1;

    // Call the function
    int result = writePatientData(ssn, name, arrivalTime, arrivalDate, departureTime, departureDate, infectious, seatingNumber);

    // Check if the function call was successful
    REQUIRE(result == 0);

    // Read the written data from the file and verify its correctness
    FILE *file = fopen(PATH_TO_PATIENT_DATA_CSV_FILE, "r");
    char buffer[100];
    fgets(buffer, sizeof(buffer), file);
    fclose(file);

    // Compare the written data with the expected data
    char expectedOutput[100];
    sprintf(expectedOutput, "%lu,%s,%i,%li,%i,%li,%c,%i\n", ssn, name, arrivalTime, arrivalDate, departureTime, departureDate, infectious, seatingNumber);
    REQUIRE(strcmp(buffer, expectedOutput) == 0);
}

TEST_CASE("Test writePatientData", "[writePatientData]") {
REQUIRE(writePatientData(123456789, "Max Mustermann", 1234, 123456789, 1234, 123456789, 'Y', 1234) == CSV_WRITE_PD_EXECUTED_SUCCESSFULLY_AND_CRERATED_FILE);
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

