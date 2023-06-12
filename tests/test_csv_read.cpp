//#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "../include/otherfunctions.h"
#include "../include/CSV_read.h"
#include "../include/definitions.h"


/**
 * @brief Test case for reading a single patient from CSV.
 * @details This test case verifies that the function csv_read correctly reads a single patient from CSV and populates the patient list.
 * It checks if the patient data matches the expected values.
 */



TEST_CASE("CSV Read from Buffer - Single Patient ", "[csv_read_from_buffer]") {
    // testdata
    const char *buffer = "1234567890,John Doe,10,20220101,15,20220102,Y,5";

    //create new patient list
    PatientList *head = (PatientList *)malloc(sizeof(PatientList));
    head->data = NULL;
    head->next = NULL;

    int result = csv_read_from_buffer(head, buffer);

    REQUIRE(result == 1); // check if successful

    // Compare buffer with Patientrecord
    REQUIRE(head->data != NULL);
    REQUIRE(head->data->ssn == 1234567890);
    REQUIRE(strcmp(head->data->name, "John Doe") == 0);
    REQUIRE(head->data->arrivalTime == 10);
    REQUIRE(head->data->arrivalDate == 20220101);
    REQUIRE(head->data->departureTime == 15);
    REQUIRE(head->data->departureDate == 20220102);
    REQUIRE(head->data->infectious == 'Y');
    REQUIRE(head->data->seatingNumber == 5);

    
    free(head->data);
    free(head);
}
/**
 * @brief Test case for csv_read_from_buffer function with multiple patients.
 *
 * This test case verifies the functionality of the csv_read_from_buffer function by passing a buffer
 * with multiple patient records. It checks if the function successfully reads all the patient records
 * from the buffer and adds them to the patient list.
 */
/*TEST_CASE("CSV Read from Buffer - Multiple Patients", "[csv_read_from_buffer]") {
    const char *buffer = "1234567890,John Doe,10,20220101,15,20220102,Y,5\n"
                         "9876543210,Jane Smith,9,20220103,14,20220104,N,3\n"
                         "5678901234,Michael Johnson,8,20220105,13,20220106,Y,7\n";

    PatientList *head = (PatientList *)malloc(sizeof(PatientList));
    head->data = NULL;
    head->next = NULL;

    int result = csv_read_from_buffer(head, buffer);

    REQUIRE(result == 1);

    REQUIRE(head->data != NULL);
    REQUIRE(head->data->ssn == 1234567890);
    REQUIRE(strcmp(head->data->name, "John Doe") == 0);
    REQUIRE(head->data->arrivalTime == 10);
    REQUIRE(head->data->arrivalDate == 20220101);
    REQUIRE(head->data->departureTime == 15);
    REQUIRE(head->data->departureDate == 20220102);
    REQUIRE(head->data->infectious == 'Y');
    REQUIRE(head->data->seatingNumber == 5);

    PatientList *nextPatient = head->next;
    REQUIRE(nextPatient != NULL);
    REQUIRE(nextPatient->data->ssn == 9876543210);
    REQUIRE(strcmp(nextPatient->data->name, "Jane Smith") == 0);
    REQUIRE(nextPatient->data->arrivalTime == 9);
    REQUIRE(nextPatient->data->arrivalDate == 20220103);
    REQUIRE(nextPatient->data->departureTime == 14);
    REQUIRE(nextPatient->data->departureDate == 20220104);
    REQUIRE(nextPatient->data->infectious == 'N');
    REQUIRE(nextPatient->data->seatingNumber == 3);

    nextPatient = nextPatient->next;
    REQUIRE(nextPatient != NULL);
    REQUIRE(nextPatient->data->ssn == 5678901234);
    REQUIRE(strcmp(nextPatient->data->name, "Michael Johnson") == 0);
    REQUIRE(nextPatient->data->arrivalTime == 8);
    REQUIRE(nextPatient->data->arrivalDate == 20220105);
    REQUIRE(nextPatient->data->departureTime == 13);
    REQUIRE(nextPatient->data->departureDate == 20220106);
    REQUIRE(nextPatient->data->infectious == 'Y');
    REQUIRE(nextPatient->data->seatingNumber == 7);

    // Freigabe des Speichers
    while (head != NULL) {
        PatientList *next = head->next;
        free(head->data);
        free(head);
        head = next;
    }
}*/





