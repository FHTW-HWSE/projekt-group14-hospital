// Testregion



#include <catch2/catch.hpp>
#include <cstdint>
#include "../include/definitions.h"
#include "../include/CSV_write.h"


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

