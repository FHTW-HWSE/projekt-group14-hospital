#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "../include/otherfunctions.h"
#include "../include/CSV_read.h"
TEST_CASE("CSV Read - Single Patient Test", "[csv_read]") {
    // create Single patient
    PatientRecord testData = {123456789, "John Doe", 10, 20230101, 15, 20230102, 'N', 1};

    // create empty patientlist
    PatientList *HEAD = new PatientList();
    HEAD->data = nullptr;
    HEAD->next = nullptr;

    // connecting testdata to patientlist
    PatientList *listElement = new PatientList();
    listElement->data = &testData;
    listElement->next = nullptr;
    HEAD->data = &testData;
    HEAD->next = nullptr;

    // read testdata
    int result = csv_read(HEAD);

    // result should be higher than -1
    REQUIRE(result >= 0);

    // compare read data with test data
    PatientRecord *patient = HEAD->data;
    REQUIRE(patient->ssn == testData.ssn);
    REQUIRE(strcmp(patient->name, testData.name) == 0);
    REQUIRE(patient->arrivalTime == testData.arrivalTime);
    REQUIRE(patient->arrivalDate == testData.arrivalDate);
    REQUIRE(patient->departureTime == testData.departureTime);
    REQUIRE(patient->departureDate == testData.departureDate);
    REQUIRE(patient->infectious == testData.infectious);
    REQUIRE(patient->seatingNumber == testData.seatingNumber);

    // free list
    free_list(HEAD);
}

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


