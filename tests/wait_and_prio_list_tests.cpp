
#include <catch2/catch.hpp>
#include "../include/otherfunctions.h"


TEST_CASE("Test getPrioList function", "[getPrioList]") {
    // Create a test patient list
    PatientList *head = (PatientList *)malloc(sizeof(PatientList));
    PatientList *node1 = (PatientList *)malloc(sizeof(PatientList));
    PatientList *node2 = (PatientList *)malloc(sizeof(PatientList));
    PatientList *node3 = (PatientList *)malloc(sizeof(PatientList));

    head->data = (PatientRecord *)malloc(sizeof(PatientRecord));
    head->data->seatingNumber = -1;
    head->data->departureDate = 0;
    head->next = node1;

    node1->data = (PatientRecord *)malloc(sizeof(PatientRecord));
    node1->data->seatingNumber = -1;
    node1->data->departureDate = 0;
    node1->next = node2;

    node2->data = (PatientRecord *)malloc(sizeof(PatientRecord));
    node2->data->seatingNumber = 10;
    node2->data->departureDate = 0;
    node2->next = node3;

    node3->data = (PatientRecord *)malloc(sizeof(PatientRecord));
    node3->data->seatingNumber = -1;
    node3->data->departureDate = 0;
    node3->next = NULL;

    // Call the getPrioList function
    PatientList *prioList = getPrioList(head);

    // Check if the returned list is sorted correctly
    REQUIRE(prioList->data->seatingNumber == -1);
    REQUIRE(prioList->next->data->seatingNumber == -1);

    // Clean up the test patient list
    free(node3->data);
    free(node3);
    free(node2->data);
    free(node2);
    free(node1->data);
    free(node1);
    free(head->data);
    free(head);
    free(prioList);
}

TEST_CASE("Test getWaitList function", "[getWaitList]") {
    // Create a test patient list
    PatientList *head = (PatientList *)malloc(sizeof(PatientList));
    PatientList *node1 = (PatientList *)malloc(sizeof(PatientList));
    PatientList *node2 = (PatientList *)malloc(sizeof(PatientList));
    PatientList *node3 = (PatientList *)malloc(sizeof(PatientList));

    head->data = (PatientRecord *)malloc(sizeof(PatientRecord));
    head->data->seatingNumber = 5;
    head->data->departureDate = 0;
    head->next = node1;

    node1->data = (PatientRecord *)malloc(sizeof(PatientRecord));
    node1->data->seatingNumber = -1;
    node1->data->departureDate = 0;
    node1->next = node2;

    node2->data = (PatientRecord *)malloc(sizeof(PatientRecord));
    node2->data->seatingNumber = 8;
    node2->data->departureDate = 0;
    node2->next = node3;

    node3->data = (PatientRecord *)malloc(sizeof(PatientRecord));
    node3->data->seatingNumber = 3;
    node3->data->departureDate = 0;
    node3->next = NULL;

    // Call the getWaitList function
    PatientList *waitList = getWaitList(head);

    // Check if the returned list is sorted correctly
    REQUIRE(waitList->data->seatingNumber == 3);
    REQUIRE(waitList->next->data->seatingNumber == 5);
    REQUIRE(waitList->next->next->data->seatingNumber == 8);

    // Clean up the test patient list
    free(node3->data);
    free(node3);
    free(node2->data);
    free(node2);
    free(node1->data);
    free(node1);
    free(head->data);
    free(head);
    free(waitList);
}
