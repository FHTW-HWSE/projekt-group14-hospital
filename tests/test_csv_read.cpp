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



TEST_CASE("CSV Read - Single Patient Test", "[csv_read]") {
    // Create a test patient list
    PatientList *head = (PatientList *)malloc(sizeof(PatientList));
    PatientList *node1 = (PatientList *)malloc(sizeof(PatientList));
    PatientList *node2 = (PatientList *)malloc(sizeof(PatientList));
    PatientList *node3 = (PatientList *)malloc(sizeof(PatientList));

    head->data = (PatientRecord *)malloc(sizeof(PatientRecord));
    head->data->ssn = 123456789;
    strcpy(head->data->name, "John Doe");
    head->data->arrivalTime = 10;
    head->data->arrivalDate = 20230101;
    head->data->departureTime = 15;
    head->data->departureDate = 20230102;
    head->data->infectious = 'N';
    head->data->seatingNumber = -1;
    head->next = node1;

    node1->data = (PatientRecord *)malloc(sizeof(PatientRecord));
    node1->data->ssn = 987654321;
    strcpy(node1->data->name, "Jane Smith");
    node1->data->arrivalTime = 8;
    node1->data->arrivalDate = 20230103;
    node1->data->departureTime = 12;
    node1->data->departureDate = 20230104;
    node1->data->infectious = 'Y';
    node1->data->seatingNumber = -1;
    node1->next = node2;

    node2->data = (PatientRecord *)malloc(sizeof(PatientRecord));
    node2->data->ssn = 456789123;
    strcpy(node2->data->name, "Bob Johnson");
    node2->data->arrivalTime = 14;
    node2->data->arrivalDate = 20230105;
    node2->data->departureTime = 18;
    node2->data->departureDate = 20230106;
    node2->data->infectious = 'N';
    node2->data->seatingNumber = 10;
    node2->next = node3;

    node3->data = (PatientRecord *)malloc(sizeof(PatientRecord));
    node3->data->ssn = 789123456;
    strcpy(node3->data->name, "Alice Davis");
    node3->data->arrivalTime = 9;
    node3->data->arrivalDate = 20230107;
    node3->data->departureTime = 13;
    node3->data->departureDate = 20230108;
    node3->data->infectious = 'N';
    node3->data->seatingNumber = -1;
    node3->next = NULL;

    // Read the test data
    int result = csv_read(head);

    // Check the result
    REQUIRE(result >= 0);

    // Compare read data with test data
    PatientRecord *patient = head->data;
    REQUIRE(patient->ssn == 123456789);
    REQUIRE(strcmp(patient->name, "John Doe") == 0);
    REQUIRE(patient->arrivalTime == 10);
    REQUIRE(patient->arrivalDate == 20230101);
    REQUIRE(patient->departureTime == 15);
    REQUIRE(patient->departureDate == 20230102);
    REQUIRE(patient->infectious == 'N');
    REQUIRE(patient->seatingNumber == -1);

    // Free the memory
    free(head->data);
    free(node1->data);
    free(node2->data);
    free(node3->data);
    free(head);
    free(node1);
    free(node2);
    free(node3);
}

/**
 * @brief Test case for reading multiple patients from CSV.
 * @details This test case verifies that the function csv_read correctly reads multiple patients from CSV and populates the patient list.
 * It checks if the number of patients in the list matches the expected value.
 */

TEST_CASE("CSV Read - Multiple Patients Test", "[csv_read]") {
    // creating testdata
    PatientRecord testData[5] = {
        {123456789, "John Doe", 10, 20230101, 15, 20230102, 'N', 1},
        {987654321, "Jane Smith", 8, 20230101, 12, 20230102, 'N', 2},
        {567890123, "Alice Johnson", 9, 20230101, 14, 20230102, 'N', 3},
        {456789012, "Bob Williams", 11, 20230101, 16, 20230102, 'N', 4},
        {234567890, "Emily Davis", 13, 20230101, 18, 20230102, 'N', 5}
    };

    // create empty patienlist
    PatientList *HEAD = (PatientList *)malloc(sizeof(PatientList));
    HEAD->data = NULL;
    HEAD->next = NULL;

    // connect testdata to patientlist
    for (int i = 0; i < 5; i++) {
        PatientList *listElement = (PatientList *)malloc(sizeof(PatientList));
        listElement->data = &testData[i];
        listElement->next = NULL;

        if (HEAD->data == NULL) {
            HEAD->data = &testData[i];
            HEAD->next = NULL;
        } else {
            PatientList *current = HEAD;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = listElement;
        }
    }

    // read testdata
    int result = csv_read(HEAD);

    // result should be higher than -1
    REQUIRE(result >= 0);

    // get number of patients from list
    int count = 0;
    PatientList *current = HEAD;
    while (current != NULL) {
        count++;
        current = current->next;
    }

    REQUIRE(count == result);

    // free list
    free_list(HEAD);
}

//what else? null pointer übergeben, pointer nicht null aber next data null


