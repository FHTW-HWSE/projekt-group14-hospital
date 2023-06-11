
#include <catch2/catch.hpp>
#include "../include/dateFunctions.h"
#include "../include/otherfunctions.h"

TEST_CASE("Time_returned_in_hhmm_format_as_int", "getTime()") {
    int result = getTime();

    REQUIRE(result <= 2359);
    REQUIRE(result >= 0);
}

TEST_CASE("Time_returned_in_yyyymmdd_format_as_int", "getDate()") {
    int result = getDate();

    REQUIRE(result <= 99991231);
    REQUIRE(result >=20230101);
}

TEST_CASE("Find_existing_patient", "findPatient()") {
    // Create a PatientList with a patient that has the given social security number (soz)
    unsigned long soz = 1234; // Replace with the desired social security number
    PatientList* head = (PatientList*) malloc(sizeof(PatientList));
    head->data = (PatientRecord*) malloc(sizeof(PatientRecord));
    head->data->ssn = soz;
    head->next = NULL;

    // Call the findPatient function
    PatientRecord* result = findPatient(head, soz);

    // Check if the result is not NULL and has the correct social security number
    REQUIRE(result != NULL);
    REQUIRE(result->ssn == soz);

    // Clean up memory
    free(head->data);
    free(head);
}

TEST_CASE("Find_nonexistent_patient", "findPatient()") {
    // Create an empty PatientList
    PatientList* head = NULL;

    // Call the findPatient function with a social security number that doesn't exist
    unsigned long soz = 987654321; // Replace with a social security number that doesn't exist
    PatientRecord* result = findPatient(head, soz);

    // Check if the result is NULL
    REQUIRE(result == NULL);
}

TEST_CASE("Get_seat_neighbour", "getSeatNeighbour()") {
    // Create a PatientList with patients seated in the same row as the infected patient
    PatientList* head = (PatientList*) malloc(sizeof(PatientList));
    PatientList *node1 = (PatientList *)malloc(sizeof(PatientList));
    PatientList *node2 = (PatientList *)malloc(sizeof(PatientList));

    head->data = (PatientRecord*) malloc(sizeof(PatientRecord));
    head->data->ssn = 1234;
    head->data->seatingNumber = 5; // Replace with the desired seating number
    head->data->arrivalDate = 20220101; // Replace with the desired arrival date
    head->data->arrivalTime = 1200; // Replace with the desired arrival time
    head->data->departureDate = 20220105; // Replace with the desired departure date
    head->data->departureTime = 1300; // Replace with the desired departure time
    head->next = node1;

    node1->data = (PatientRecord *)malloc(sizeof(PatientRecord));
    node1->data->ssn = 1235;
    node1->data->seatingNumber = 2; // Replace with the desired seating number
    node1->data->arrivalDate = 20220102; // Replace with the desired arrival date
    node1->data->arrivalTime = 1300; // Replace with the desired arrival time
    node1->data->departureDate = 20220105; // Replace with the desired departure date
    node1->data->departureTime = 1400; // Replace with the desired departure time
    node1->next = node2;

    node2->data = (PatientRecord *)malloc(sizeof(PatientRecord));
    node2->data->ssn = 1232;
    node2->data->seatingNumber = 15; // Replace with the desired seating number
    node2->data->arrivalDate = 20211231; // Replace with the desired arrival date
    node2->data->arrivalTime = 1200; // Replace with the desired arrival time
    node2->data->departureDate = 20220105; // Replace with the desired departure date
    node2->data->departureTime = 1400; // Replace with the desired departure time
    node2->next = NULL;

    // Call the getSeatNeighbour function
    PatientList* result = getSeatNeighbour(head, 1234); // Replace 1234 with the desired social security number

    // Check if the result is not NULL
    REQUIRE(result != NULL);

    // Loop through the result list and check the seat numbers of the neighbours
    PatientList* current = result;
    while (current != NULL) {
        REQUIRE(current->data != NULL);
        REQUIRE(current->data->seatingNumber >= 0); // Replace with the desired seating number range
        REQUIRE(current->data->seatingNumber <= 10); // Replace with the desired seating number range
        current = current->next;
    }
    
    // Clean up memory
    while (result != NULL) {
        PatientList* temp = result;
        result = result->next;
        free(temp->data);
        free(temp);
    }
    free(head->data);
    free(head);
}

TEST_CASE("Swap_patients", "swapPatients()") {
    // Create two patients to swap
    PatientList* a = (PatientList*) malloc(sizeof(PatientList));
    a->data = (PatientRecord*) malloc(sizeof(PatientRecord));
    a->next = NULL;

    PatientList* b = (PatientList*) malloc(sizeof(PatientList));
    b->data = (PatientRecord*) malloc(sizeof(PatientRecord));
    b->next = NULL;

    // Assign some values to the patients' data for testing
    a->data->arrivalDate = 20220101;
    a->data->arrivalTime = 1200;

    b->data->arrivalDate = 20220102;
    b->data->arrivalTime = 1300;

    // Call the swapPatients function
    swapPatients(a, b);

    // Check if the patients' data has been swapped correctly
    REQUIRE(a->data->arrivalDate == 20220102);
    REQUIRE(a->data->arrivalTime == 1300);
    REQUIRE(b->data->arrivalDate == 20220101);
    REQUIRE(b->data->arrivalTime == 1200);

    // Clean up memory
    free(a->data);
    free(a);
    free(b->data);
    free(b);
}

TEST_CASE("Sort_patients", "sortPatients()") {
    // Create a PatientList with multiple patients
    PatientList* head = (PatientList*) malloc(sizeof(PatientList));
    head->data = (PatientRecord*) malloc(sizeof(PatientRecord));
    head->data->arrivalDate = 20220102;
    head->data->arrivalTime = 1200;

    PatientList* second = (PatientList*) malloc(sizeof(PatientList));
    second->data = (PatientRecord*) malloc(sizeof(PatientRecord));
    second->data->arrivalDate = 20220101;
    second->data->arrivalTime = 1300;

    PatientList* third = (PatientList*) malloc(sizeof(PatientList));
    third->data = (PatientRecord*) malloc(sizeof(PatientRecord));
    third->data->arrivalDate = 20220103;
    third->data->arrivalTime = 1100;

    head->next = second;
    second->next = third;
    third->next = NULL;

    // Call the sortPatients function
    sortPatients(head);

    // Check if the patients are sorted in ascending order based on arrival date and time
    REQUIRE(head->data->arrivalDate == 20220101);
    REQUIRE(head->data->arrivalTime == 1300);
    REQUIRE(second->data->arrivalDate == 20220102);
    REQUIRE(second->data->arrivalTime == 1200);
    REQUIRE(third->data->arrivalDate == 20220103);
    REQUIRE(third->data->arrivalTime == 1100);

    // Clean up memory
    free(head->data);
    free(second->data);
    free(third->data);
    free(third);
    free(second);
    free(head);
}

TEST_CASE("Compare_patients", "compare()") {
    // Create two patient records for comparison
    PatientRecord* patient1 = (PatientRecord*) malloc(sizeof(PatientRecord));
    patient1->arrivalDate = 20220101;
    patient1->arrivalTime = 1200;

    PatientRecord* patient2 = (PatientRecord*) malloc(sizeof(PatientRecord));
    patient2->arrivalDate = 20220101;
    patient2->arrivalTime = 1300;

    // Call the compare function
    int result = compare(patient1, patient2);

    // Check the result of the comparison
    REQUIRE(result < 0); // Expecting a negative value since patient1 arrives earlier

    // Clean up memory
    free(patient1);
    free(patient2);
}


/* Problem bc it writes into our DB bc of updateCSV() in the function
TEST_CASE("Check if updateInfection changed", "updateInfection()") {
    // Create a test patient list
    PatientList *head = (PatientList *)malloc(sizeof(PatientList));
    PatientList *node1 = (PatientList *)malloc(sizeof(PatientList));
    PatientList *node2 = (PatientList *)malloc(sizeof(PatientList));
    PatientList *node3 = (PatientList *)malloc(sizeof(PatientList));

    head->data = (PatientRecord *)malloc(sizeof(PatientRecord));
    head->data->ssn = 1234567890;
    head->data->infectious = 'Y';
    head->next = node1;

    node1->data = (PatientRecord *)malloc(sizeof(PatientRecord));
    node1->data->ssn = 2134567890;
    node1->data->infectious = 'N';
    node1->next = NULL;

    // Call the updateInfection function
    updateInfection(head, 1234567890);
    updateInfection(head, 2134567890);

    // Check if the returned list is correctly
    REQUIRE(head->data->infectious == 'N');
    REQUIRE(node1->data->infectious == 'Y');

    // Clean up the test patient list
    free(node2->data);
    free(node2);
    free(node1->data);
    free(node1);
    free(head->data);
    free(head);
}
*/