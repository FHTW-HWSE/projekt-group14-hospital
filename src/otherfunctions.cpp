#include "../include/otherfunctions.h"
#include "../include/CSV_read.h"
#include "../include/CSV_write.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "../include/dateFunctions.h"
#include "../include/printFunctions.h"
#include <ctype.h>

#pragma region SEATING NEIGHBOUR
PatientList *getSeatNeighbour(PatientList *head, unsigned long soz)
{
    PatientList *patient = head;
    PatientRecord *infectpat;
    PatientList *neighbours = (PatientList *)malloc(sizeof(PatientList));
    PatientList *headNeighbour = neighbours;

    // initaliserung
    neighbours->data = NULL;
    neighbours->next = NULL;

    // hilfsvariable
    int seatingMin = 0;
    int seatingMax = 0;

    // get data for infected patient
    infectpat = findPatient(head, soz);

    // check seating
    if (infectpat->seatingNumber < 0)
    {
        return headNeighbour;
    }
    else if (infectpat->seatingNumber <= 5)
    {
        seatingMin = 0;
        seatingMax = 5;
    }
    else if (infectpat->seatingNumber <= 10)
    {
        seatingMin = 6;
        seatingMax = 10;
    }
    else if (infectpat->seatingNumber <= 15)
    {
        seatingMin = 11;
        seatingMax = 15;
    }
    else if (infectpat->seatingNumber <= 20)
    {
        seatingMin = 16;
        seatingMax = 20;
    }
    else if (infectpat->arrivalDate <= 25)
    {
        seatingMin = 21;
        seatingMax = 25;
    }
    else
    {
        return headNeighbour;
    }

    // extremly complicated code, made by a rookie
    while (patient != NULL)
    {
        if (patient->data != infectpat)
        {
            if (patient->data->seatingNumber <= seatingMax && patient->data->seatingNumber >= seatingMin) //Check ob in selber Reihe saßen
            {
                long infDepDate = 0;
                long patDepDate = 0;
                if (patient->data->departureDate == 0) //Sollte infected Patient noch vor Ort sein -> dep Date und Time bekommen
                    patDepDate = getDate();
                else
                    patDepDate = patient->data->departureDate;
                if (infectpat->departureDate == 0)
                    infDepDate = getDate();
                else
                    infDepDate = infectpat->departureDate;
                if (infectpat->arrivalDate <= patDepDate && patient->data->arrivalDate <= infDepDate) //InfectP Arr vor dem Dep der ContactP && ContactP Arr vor dem Dep InfectP
                {
                    if (patient->data->arrivalDate < infDepDate) //Abfangen eines Cornercases -> Dep Date CP vorm Dep Date infP (Time Vergleich damit irrelevant)
                    {
                        if (neighbours->data == NULL)
                        {
                            neighbours->data = patient->data;
                        }
                        else
                        {
                            neighbours->next = (PatientList *)malloc(sizeof(PatientList));
                            neighbours = neighbours->next;
                            neighbours->data = patient->data;
                            neighbours->next = NULL;
                        }
                    }
                    else //Check der DepTime weil am selben Tag
                    {
                        int infDepTime = 0;
                        int patDepTime = 0;
                        if (patient->data->departureTime == 0) //Abfangen von vorort -> Time in Dep
                            patDepTime = getTime();
                        else
                            patDepTime = patient->data->departureTime;
                        if (infectpat->departureTime == 0)
                            infDepTime = getTime();
                        else
                            infDepTime = infectpat->departureTime;
                        if (infectpat->arrivalTime <= patDepTime && patient->data->arrivalTime <= infDepTime) //InfectP Arr vor dem Dep der ContactP && ContactP Arr vor dem Dep InfectP
                        {
                            if (neighbours->data == NULL)
                            {
                                neighbours->data = patient->data;
                            }
                            else
                            {
                                neighbours->next = (PatientList *)malloc(sizeof(PatientList));
                                neighbours = neighbours->next;
                                neighbours->data = patient->data;
                                neighbours->next = NULL;
                            }
                        }
                    }
                }
            }
        }
        patient = patient->next;
    }
    return headNeighbour;
}

#pragma endregion

#pragma region SEARCH FOR PATIENT
PatientRecord *findPatient(PatientList *head, unsigned long soz)
{
    PatientList *patient = head;

    while (patient != NULL)
    {
        if (patient->data->ssn == soz)
        {
            return patient->data;
        }
        patient = patient->next;
    }
    printf("Error: Patient not found.\n\n");
    return NULL;
}

#pragma endregion

#pragma region PRIO & WAITING LIST

PatientList *getPrioList(PatientList *head)
{
    PatientList *prio = (PatientList *)malloc(sizeof(PatientList));
    PatientList *headPrio = prio;
    PatientList *patient = head;

    prio->data = NULL;
    prio->next = NULL;

    while (patient != NULL)
    {
        if (patient->data->seatingNumber == -1 && patient->data->departureDate == 0)
        {
            if (prio->data == NULL)
            {
                prio->data = patient->data;
            }
            else
            {
                prio->next = (PatientList *)malloc(sizeof(PatientList));
                prio = prio->next;
                prio->data = patient->data;
                prio->next = NULL;
            }
        }
        patient = patient->next;
    }

    // if there are no patients to prioritize, return NULL
    if (headPrio->data == NULL) {
        free_list(prio);
        return NULL;
    }

    sortPatients(headPrio);
    return headPrio;
}

PatientList *getWaitList(PatientList *head)
{
    // Create a new linked list for the wait list
    PatientList *wait = (PatientList *)malloc(sizeof(PatientList));
    PatientList *headWait = wait;
    PatientList *patient = head;

    wait->data = NULL;
    wait->next = NULL;

// Iterate through the patients in the original linked list
    while (patient != NULL)
    {
         // Check if the patient has a seating number and no departure date
        if (patient->data->seatingNumber != -1 && patient->data->departureDate == 0)
        {
            // Create a new node in the wait list and copy the patient's data
            if (wait->data == NULL)
            {
                wait->data = patient->data;
            }
            else
            {
                wait->next = (PatientList *)malloc(sizeof(PatientList));
                wait = wait->next;
                wait->data = patient->data;
                wait->next = NULL;
            }
        }
        patient = patient->next;
    }

    // if there are no patients in the waiting area, return NULL
    if (headWait->data == NULL) {
        free_list(wait);
        return NULL;
    }
     // Return the head of the wait list
    sortPatients(headWait);
    return headWait;
}

#pragma endregion

#pragma region UPDATE FUNCTIONS (departure, CSV, contact mark, infectious mark)
void addDeparture(PatientList *head, unsigned long soz)
{
    PatientRecord *patient;
    patient = findPatient(head, soz);

    patient->departureDate = getDate();
    patient->departureTime = getTime();

    updateCSV(head);
}

void updateCSV(PatientList *head)
{
    FILE *file = fopen("../programFiles/PatientData/PatientDataDB.csv", "w"); // Startpoint "src/"
    if (file == NULL)
    {
        printf("Fehler beim Öffnen der Datei.\n");
        return;
    }
    // Dateien schließen - aufgrund von "w" wurde der Inhalt gelöscht und wir haben ein leeres file
    fclose(file);

    PatientList *patient = head;
    // Befüllen der csv mit neuen Daten
    while (patient != NULL)
    {
        writePatientData(patient->data->ssn, patient->data->name, patient->data->arrivalTime, patient->data->arrivalDate,
                         patient->data->departureTime, patient->data->departureDate, patient->data->infectious, patient->data->seatingNumber);
        patient = patient->next;
    }
}

void updateContact(PatientList *head, PatientList *contact)
{
    PatientList* patient = head;
    PatientList* conList = contact;

    while(conList != NULL) {
        if(patient->data == conList->data && patient->data->infectious == 'N') {
            patient->data->infectious = 'C';
            conList = conList->next;
        }
        patient = patient->next;
        if(patient->data == NULL){
            patient = head;
        }
    }
    updateCSV(head);
}

void updateInfection(PatientList *head, unsigned long soz)
{
    PatientRecord *patient;
    patient = findPatient(head, soz);

    if (patient->infectious == 'Y')
    {
        patient->infectious = 'N';
        updateCSV(head);
        printf("\n\tPatient infectious status updated to: NO\n\n");
    } else if (patient->infectious == 'N')
    {
        patient->infectious = 'Y';
        updateCSV(head);
        printf("\n\tPatient infectious status updated to: YES\n\n");
    } else if (patient->infectious == 'C') 
    {
        patient->infectious = 'Y';
        updateCSV(head);
        printf("\n\tPatient infectious status updated to: YES\n\n");
    }
}

#pragma endregion

#pragma region HELPER FUNCTIONS (swap, sort, compare)
// Sort der Prio Liste (Bubblesort LinkedList)
void swapPatients(PatientList *a, PatientList *b)
{
    PatientRecord *temp = a->data;
    a->data = b->data;
    b->data = temp;
}

void sortPatients(PatientList *head)
{
    int swapped;
    PatientList *pat;
    PatientList *last = NULL;

    if (head == NULL)
    {
        return;
    }

    do
    {
        swapped = 0;
        pat = head;

        while (pat->next != last)
        {
            if (compare(pat->data, pat->next->data) > 0)
            {
                swapPatients(pat, pat->next);
                swapped = 1;
            }
            pat = pat->next;
        }
        last = pat;
    } while (swapped);
}

int compare(PatientRecord *patient1, PatientRecord *patient2)
{
    if (patient1->arrivalDate < patient2->arrivalDate)
    {
        return -1;
    }
    else if (patient1->arrivalDate > patient2->arrivalDate)
    {
        return 1;
    }
    else
    {
        if (patient1->arrivalTime < patient2->arrivalTime)
        {
            return -1;
        }
        else if (patient1->arrivalTime > patient2->arrivalTime)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

#pragma endregion

#pragma region SEATING-MAP

void printOutMap(Seat seatingMap[MAP_ROWS][MAP_COLUMNS])
{
    printf("  Seating Map\n\n");

    for (int i = 0; i < MAP_ROWS; i++)
    {
        printf("------------------------------\n|");
        for (int j = 0; j < MAP_COLUMNS; j++)
        {
            if (seatingMap[i][j].isReserved)
            {
                printf("  X | ");
            }
            else
            {
                printf(" %2d | ", seatingMap[i][j].seatNumber);
            }
        }
        printf("\n");
    }
    printf("------------------------------\n|");
}

void initializeSeatingMap(Seat seatingMap[MAP_ROWS][MAP_COLUMNS])
{
    int seatNumber = 1;
    for (int i = 0; i < MAP_ROWS; i++)
    {
        for (int j = 0; j < MAP_COLUMNS; j++)
        {
            seatingMap[i][j].seatNumber = seatNumber++;
            seatingMap[i][j].isReserved = false;
        }
    }
}

bool reserveSeatByNumber(int seatNumber, Seat seatingMap[MAP_ROWS][MAP_COLUMNS])
{
    for (int i = 0; i < MAP_ROWS; i++)
    {
        for (int j = 0; j < MAP_COLUMNS; j++)
        {
            if (seatingMap[i][j].seatNumber == seatNumber)
            {
                if (!seatingMap[i][j].isReserved)
                {
                    seatingMap[i][j].isReserved = true;
                    return true;
                }
                break;
            }
        }
    }
    return false;
}

bool cancelReservationByNumber(int seatNumber, Seat seatingMap[MAP_ROWS][MAP_COLUMNS])
{
    for (int i = 0; i < MAP_ROWS; i++)
    {
        for (int j = 0; j < MAP_COLUMNS; j++)
        {
            if (seatingMap[i][j].seatNumber == seatNumber)
            {
                if (seatingMap[i][j].isReserved)
                {
                    seatingMap[i][j].isReserved = false;
                    return true;
                }
                break;
            }
        }
    }
    return false;
}

void reserveSeatsFromPatientList(PatientList *patientList, Seat seatingMap[MAP_ROWS][MAP_COLUMNS])
{
    PatientList *currentPatientNode = patientList;

    // loop through list
    while (currentPatientNode != NULL)
    {
        int seatNumber = currentPatientNode->data->seatingNumber;

        // check that the seat number is greater than 0 and does not exceed the total number of seats
        if (seatNumber > 0 && seatNumber <= MAP_ROWS * MAP_COLUMNS && currentPatientNode->data->departureDate == 0)
        {
            // reserve seat
            reserveSeatByNumber(seatNumber, seatingMap);
        }

        // next patient
        currentPatientNode = currentPatientNode->next;
    }
}

#pragma endregion

#pragma region ADD NEW PATIENTS
bool isNumericInput(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isdigit(str[i]))
        {
            return false;
        }
    }
    return true;
}

bool isValidSSN(const char *str)
{
    return (strlen(str) == 10 && isNumericInput(str));
}

unsigned long convertSSN(const char *str)
{
    char *endptr;
    unsigned long ssn = strtoul(str, &endptr, 10);

    if (endptr == str || *endptr != '\0')
    {
        return 0; // Ungültige Eingabe
    }

    return ssn;
}

unsigned long getSSNfromUser()
{
    unsigned long ssn = 0;
    char buffer[20];
    int attempts = 0;
    while (true)
    {
        if (attempts >= 5)
        {
            printf("Invalid input entered too many times. Exiting...\n");
            return 0;
        }
        printf("Please enter the patient's social security number (FORMAT: 0000YYMMDD): ");
        if (fgets(buffer, sizeof(buffer), stdin) != NULL)
        {
            buffer[strcspn(buffer, "\n")] = '\0'; // Zeilenumbruch entfernen

            if (!isValidSSN(buffer))
            {
                attempts++;
                printf("Invalid input! Please enter a 10-digit numeric value.\n");
            }
            else
            {
                ssn = convertSSN(buffer);
                break;
            }
        }
        else
        {
            attempts++;
            printf("Error reading input.\n");
            break;
        }
    }

    return ssn;
}

void enterPatientName(PatientRecord *patient)
{
    printf("\nPlease enter the patient's name (FORMAT: Surname Forename): ");
    fgets(patient->name, MAX_PATIENT_NAME, stdin);
    patient->name[strcspn(patient->name, "\n")] = '\0'; // Remove newline character
}

bool enterInfectiousStatus(PatientRecord *patient)
{
    int attempts = 0;
    printf("\nIs the patient infectious? [Y/N]: ");

    while (true)
    {
        char c = getchar();
        if (getchar() != '\n')
        {
            while (getchar() != '\n')
                ; // Discard extra characters
        }
        switch (tolower(c))
        {
        case 'y':
            patient->infectious = 'Y';
            return true;
        case 'n':
            patient->infectious = 'N';
            return true;
        default:
            attempts++;
            if (attempts >= 5)
            {
                printf("Invalid input entered too many times. Exiting...\n");
                return false;
            }
            printf("Invalid input! Please enter 'Y' or 'N': ");
            continue;
        }
    }
}

int selectSeatingNumber(Seat seatingMap[MAP_ROWS][MAP_COLUMNS])
{
    int seatingNumber;
    printf("Please enter the seating number (1-%d): ", MAP_ROWS * MAP_COLUMNS);
    int attempts = 0;
    while (true)
    {
        int result = scanf("%d", &seatingNumber);
        while (getchar() != '\n')
            ; // Discard extra characters

        if (result == 1 && seatingNumber >= 1 && seatingNumber <= (MAP_ROWS * MAP_COLUMNS))
        {
            if (!reserveSeatByNumber(seatingNumber, seatingMap))
            {
                printf("Seat %d is already taken! Please enter another seating number (1-%d): ", seatingNumber, MAP_ROWS * MAP_COLUMNS);
            }
            else
            {
                return seatingNumber;
            }
        }
        else
        {
            attempts++;
            if (attempts >= 5)
            {
                printf("Invalid input entered too many times. Exiting...\n");
                return -1;
            }
            printf("Invalid input! Please enter a valid seating number between 1 and %d: ", MAP_ROWS * MAP_COLUMNS);
        }
    }
}

bool enterModeOfArrival(PatientRecord *patient, Seat seatingMap[MAP_ROWS][MAP_COLUMNS])
{
    printf("\nPlease press 'a' if the patient came by ambulance or 'o' if they came by themselves: ");
    int attempts = 0;
    while (true)
    {
        char c = getchar();
        if (getchar() != '\n')
        {
            while (getchar() != '\n')
                ;
        }
        switch (tolower(c))
        {
        case 'a':
            patient->seatingNumber = -1;
            printf("Patient by ambulance - saved!\n");
            return true;
        case 'o':
            patient->seatingNumber = selectSeatingNumber(seatingMap);
            if (patient->seatingNumber == -1)
                return false;
            else
            {
                printf("Patient came by themselves - saved!\n");
                return true;
            }
        default:
            attempts++;
            if (attempts > 5)
            {
                printf("Invalid input entered too many times. Exiting...\n");
                return false;
            }
            printf("Invalid input! Please enter 'a' or 'o': ");

            continue;
        }
    }
}

int addNewPatient(Seat seatingMap[MAP_ROWS][MAP_COLUMNS])
{
    PatientRecord tempPatient = {0, "x", 0, 0, 0, 0, 'N'};

    unsigned long ssn = getSSNfromUser();
    if (ssn == 0)
    {
        printf("Error: Invalid social security number.\n");
        return 1;
    }
    tempPatient.ssn = ssn;

    enterPatientName(&tempPatient);
    tempPatient.arrivalTime = getTime();
    tempPatient.arrivalDate = getDate();
    if (enterInfectiousStatus(&tempPatient) == false)
        return 1;
    if (enterModeOfArrival(&tempPatient, seatingMap) == false)
        return 1;

    M_WRITEPATIENTDATASTRUCT((&tempPatient));

    /*TESTPRINT*/
    printf("Saved Patient Record:\n"
           "SSN: %lu | Name: %s | Arrival Time: %d | Arrival Date: %ld | Infectious: %c | Seating Number: %d\n",
           tempPatient.ssn, tempPatient.name, tempPatient.arrivalTime, tempPatient.arrivalDate,
           tempPatient.infectious, tempPatient.seatingNumber);

    return 0;
}

#pragma endregion

#pragma region MENU
int menu(Seat seatingMap[MAP_ROWS][MAP_COLUMNS])
{
    int static checkDefault = 0;
    PatientList *head = (PatientList *)malloc(sizeof(PatientList));

    head->data = NULL;
    head->next = NULL;
    csv_read(head);
    reserveSeatsFromPatientList(head, seatingMap);

    PatientList *prio = (PatientList *)malloc(sizeof(PatientList));
    PatientList *wait = (PatientList *)malloc(sizeof(PatientList));
    PatientList *patNeighbours = (PatientList *)malloc(sizeof(PatientList));
    PatientRecord *pat = (PatientRecord *)malloc(sizeof(PatientRecord));
    PatientRecord *tempPat = (PatientRecord *)malloc(sizeof(PatientRecord));
    unsigned long ssn = 0;
    while (1)
    {

        printf("You are now in the menu...\n"
               "\t- Press 'n' to create a new patient\n"
               "\t- Press 'd' to display a list of all patients\n"
               "\t- Press 's' to search for a patient & their information\n"
               "\t- Press 'p' to display the prioritization list\n"
               "\t- Press 'w' to display the waiting area list\n"
               "\t- Press 'c' to change the infectious status of a patient\n"
               "\t- Press 'i' to display infectious patients incl. seat neighbors\n"
               "\t- Press 'm' to display the current seating map\n"
               "\t- Press 't' to remove of a patient through successful treatment\n"
               "\t- Press 'q' to close the program\n");

        int c = getchar();
        if (getchar() != '\n')
        {
            while (getchar() != '\n')
                ; // to catch all characters if user enters too many
        }

        switch (c)
        {
        /***Create new patient***/
        case 'n':
            if (addNewPatient(seatingMap) == 0)
                printf("patient saved successfully!\n"
                "If you want to proceed with the new patient saved " 
                "in the database, please restart the programm!\n\n");
            
            break;
        /***Display patient list***/
        case 'd':              
            printPatientList(head, WHOLE);    
            
            break;
        /***Search for a patient & print out infos******/
        case 's':
            ssn = getSSNfromUser();
            if (ssn == 0) { 
                printf("Error: Invalid social security number.\n");}
            pat = findPatient(head, ssn);
            if(pat == NULL) break;
            else{
                printf("Info of the patient:\n");
                printf("\tSSN: %-10lu\n\tPatient name: %-30s\n",pat->ssn, pat->name);
                printf("\tArrival time & date (YYMMDD): %d:%d\t%lu\n", pat->arrivalTime/100, pat->arrivalTime%100, pat->arrivalDate);
                if (pat->departureDate > 0){
                   printf("\tDepature time & date (YYMMDD): %d:%d\t%lu\n", pat->departureTime/100, pat->departureTime%100, pat->departureDate);
                } else printf("\tPatient is still in treatment\n");
                
                  printf("\tInfectious & Seating number: %c\t %d\n\n",pat->infectious, pat->seatingNumber);
            }
            
            break;

                
            /***Showing priorization list***/
            case 'p':
                prio = getPrioList(head);
                if(prio == NULL) printf("There are no patients in the prioritization list!\n\n");
                else {
                printf("\nPatients in the priorization list:\n");
                printPatientList(prio, WHOLE);
                }

                break;
            /***Change patients date***/
            case 'c':
                ssn = getSSNfromUser();
                if (ssn == 0) { printf("Error: Invalid social security number.\n");} 
                else {
                updateInfection(head, ssn);
                ssn = 0;
                }

                break;
            /***Display patients in the waiting area***/
            case 'w':
                wait = getWaitList(head);
                if(wait == NULL) printf("There are no patients in the waiting area!\n\n");
                else {
                printf("\nPatients in the waiting area:\n");
                printPatientList(wait, WHOLE);
                }

                break;
            /***Display infectious patients incl. seat neighbors***/
            case 'i':
                printf("Seat neighbors of infectious patient\n");
    //TEST with 5678901111
                ssn = getSSNfromUser();
                if (ssn == 0) { printf("Error: Invalid social security number.\n");} 
                else {
                patNeighbours = getSeatNeighbour(head, ssn);
                if (patNeighbours->data == NULL)
                    printf("No seating neigbours found\n\n");
                else
                    //updateContact(head,patNeighbours);
                    printPatientList(patNeighbours, WHOLE);
                   
                    ssn = 0;
                }

                break;
            /***Display the current seating arrangements***/
            case 'm':
                printOutMap(seatingMap);

                break;
            /***Removal of a patient through successful treatment***/
            case 't':
    //TEST mit 1234566778
                
                ssn = getSSNfromUser();
                if (ssn == 0) { printf("Error: Invalid social security number.\n");}
                else {
                addDeparture(head, ssn);
                tempPat = findPatient(head, ssn);
                cancelReservationByNumber(tempPat->seatingNumber, seatingMap);
                printf("successful treatment of patient saved in database!\n\n");
                }

                break;
            /***Close program***/
            case 'q':
                printf("You chose to close the program ... bye!\n\n");
                updateCSV(head);
                free_list(head);
                freeAll(prio,wait,patNeighbours,pat,tempPat);
                return 1;
            /***Default: Wrong input -> entering again menu***/
            default:
                checkDefault++;
                if (checkDefault > 10) {
                printf("Your input could not be processed for the %dth time...\n"
                       "closing program, bye!!!\n\n\n",
                       checkDefault);
                updateCSV(head);
                free_list(head);
                freeAll(prio,wait,patNeighbours,pat,tempPat);
                return -1;
                }
                printf("Your input could not be processed! Please enter only one character\n\n");
                continue;
        }
    }
}

#pragma endregion

#pragma region ERROR MESSAGES

void printErrorMsg(int error_code)

{
    switch (error_code)
    {
    case ERR_CLOSING_FILE:
        fprintf(stderr, "An error occurred while closing a file\n");
        return;
    case ERR_OPENING_FILE:
        fprintf(stderr, "An error occurred while opening a file\n");
        return;
    case ERR_MALLOC:
        fprintf(stderr, "Error allocating memory\n");
        return;
    case ERR_WCSV_CLOSING_CSV_FILE:
        fprintf(stderr, "ERROR WriteCSV: the file could not be closed\n");
        return;
    case ERR_WCSV_OPENING_CSV_FILE:
        fprintf(stderr, "ERROR WriteCSV: the file could not be opened\n");
        return;
    case ERR_WCSV_CONVERTING_INT_TO_STRING:
        fprintf(stderr, "ERROR WriteCSV: the int could not be converted to a string\n");
        return;
    case ERR_WCSV_GENERATING_WRITE_STRING:
        fprintf(stderr, "ERROR WriteCSV: the write string could not be successfully generated\n");
        return;

    default:
        fprintf(stderr, "An Unknown Error has occured!\n");
        return;
    }
}
#pragma endregion

#pragma region FREEs

void freeAll(PatientList *prio, PatientList *wait, PatientList *patNeighbours, PatientRecord *pat, PatientRecord *tempPat){
    free(prio); 
    free(wait);
    free(patNeighbours);
    free(tempPat);
    free(pat);
}
void free_list(PatientList *head)
{
    if (head == NULL)
    {
        // list already emptyy
        return;
    }

    PatientList *current = head;

    while (current != NULL)
    {
        PatientList *temp = current;
        current = current->next;
        
        // Free the memory for the patient's data
        free(temp->data);
        // Free the memory for the node
        free(temp);
    }
}

#pragma endregion
