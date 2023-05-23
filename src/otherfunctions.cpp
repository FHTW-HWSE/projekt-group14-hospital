#include "../include/otherfunctions.h"
#include "../include/CSV_read.h"
#include "../include/CSV_write.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/dateFunctions.h"
#include "../include/printFunctions.h"
#include <ctype.h>

PatientList* getSeatNeighbour(PatientList *head, unsigned long soz) {
    PatientList *patient = head;
    PatientRecord *infectpat;
    PatientList *neighbours = (PatientList *)malloc(sizeof(PatientList));
    PatientList *headNeighbour = neighbours;

    //initaliserung
    neighbours->data = NULL;
    neighbours->next = NULL;

    //hilfsvariable
    int seatingMin = 0;
    int seatingMax = 0;

    //get data for infected patient
    infectpat = findPatient(head, soz);

    //check seating
    if(infectpat->seatingNumber < 0) {
        return NULL;
    } else if(infectpat->seatingNumber <= 5) {
        seatingMin = 0;
        seatingMax = 5;
    } else if(infectpat->seatingNumber <= 10) {
        seatingMin = 6;
        seatingMax = 10;
    } else if(infectpat->seatingNumber <= 15) {
        seatingMin = 11;
        seatingMax = 15;
    } else if(infectpat->seatingNumber <= 20) {
        seatingMin = 16;
        seatingMax = 20;
    } else if(infectpat->arrivalDate <= 25) {
        seatingMin = 21;
        seatingMax = 25;
    } else {
        return NULL;
    }

    //extremly complicated code, made by a rookie
    while (patient != NULL) {
        if(patient->data != infectpat) {
            if(patient->data->seatingNumber <= seatingMax && patient->data->seatingNumber >= seatingMin) {
                long infDepDate = 0;
                long patDepDate = 0;
                if(patient->data->departureDate == 0) patDepDate = getDate();
                else patDepDate = patient->data->departureDate;
                if(infectpat->departureDate == 0) infDepDate = getDate();
                else infDepDate = infectpat->departureDate;
                if(infectpat->arrivalDate <= patDepDate && patient->data->arrivalDate <= infDepDate) {
                    if(patient->data->arrivalDate < infDepDate) {
                        if(neighbours->data == NULL) {
                            neighbours->data = patient->data;
                        } else {
                            neighbours->next = (PatientList *)malloc(sizeof(PatientList));
                            neighbours = neighbours->next;
                            neighbours->data = patient->data;
                            neighbours->next = NULL;
                        }
                    } else {
                        int infDepTime = 0;
                        int patDepTime = 0;
                        if(patient->data->departureTime == 0) patDepTime = getTime();
                        else patDepTime = patient->data->departureTime;
                        if(infectpat->departureTime == 0) infDepTime = getTime();
                        else infDepTime = infectpat->departureTime;
                        if(infectpat->arrivalTime <= patDepTime && patient->data->arrivalTime <= infDepTime) {
                            if(neighbours->data == NULL) {
                                neighbours->data = patient->data;
                            } else {
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

PatientRecord *findPatient(PatientList *head, unsigned long soz) {
    PatientList *patient = head;
    
    while(patient != NULL) {
        if(patient->data->ssn == soz) {
            return patient->data;
        }
        patient = patient->next;
    } 
    return NULL;
}

void addDeparture(PatientList *head, unsigned long soz) {
    PatientRecord *patient;
    patient = findPatient(head, soz);

    patient->departureDate = getDate();
    patient->departureTime = getTime();

    updateCSV(head);
}

void updateInfection(PatientList *head, unsigned long soz) {
    PatientRecord *patient;
    patient = findPatient(head, soz);

    if(patient->infectious == 'N') {
        patient->infectious = 'Y';
        updateCSV(head);
    }
}

PatientList* getPrioList(PatientList *head) {
    PatientList *prio = (PatientList *)malloc(sizeof(PatientList));
    PatientList *headPrio = prio;
    PatientList *patient = head;

    prio->data = NULL;
    prio->next = NULL;

    while(patient != NULL) {
        if(patient->data->seatingNumber == -1 && patient->data->departureDate == 0) {
            if(prio->data == NULL) {
                prio->data = patient->data;
            } else {
                prio->next = (PatientList *)malloc(sizeof(PatientList));
                prio = prio->next;
                prio->data = patient->data;
                prio->next = NULL;
            }
        }
        patient = patient->next;
    }

    //if there are no patients to prioritize, return NULL
    if (headPrio->data == NULL) return NULL;
    
    sortPatients(headPrio);
    return headPrio;
}

PatientList* getWaitList(PatientList *head) {
    PatientList *wait = (PatientList *)malloc(sizeof(PatientList));
    PatientList *headWait = wait;
    PatientList *patient = head;

    wait->data = NULL;
    wait->next = NULL;

    while(patient != NULL) {
        if(patient->data->seatingNumber != -1 && patient->data->departureDate == 0) {
            if(wait->data == NULL) {
                wait->data = patient->data;
            } else {
                wait->next = (PatientList *)malloc(sizeof(PatientList));
                wait = wait->next;
                wait->data = patient->data;
                wait->next = NULL;
            }
        }
        patient = patient->next;
    }

    //if there are no patients in the waiting area, return NULL
    if (headWait->data == NULL) return NULL;

    sortPatients(headWait);
    return headWait;
}

void updateCSV(PatientList *head) {
    FILE* file = fopen("../programFiles/PatientData/PatientDataDB.csv", "w"); //Startpoint "src/"
    if (file == NULL) {
        printf("Fehler beim Öffnen der Datei.\n");
        return;
    }
    //Dateien schließen - aufgrund von "w" wurde der Inhalt gelöscht und wir haben ein leeres file
    fclose(file);

    PatientList* patient = head;
    //Befüllen der csv mit neuen Daten
    while (patient != NULL) {
        writePatientData(patient->data->ssn, patient->data->name, patient->data->arrivalTime, patient->data->arrivalDate, 
        patient->data->departureTime, patient->data->departureDate, patient->data->infectious, patient->data->seatingNumber);
        patient = patient->next;
    }
}

//Sort der Prio Liste (Bubblesort LinkedList)
void swapPatients(PatientList* a, PatientList* b) {
    PatientRecord* temp = a->data;
    a->data = b->data;
    b->data = temp;
}

void sortPatients(PatientList* head) {
    int swapped;
    PatientList* pat;
    PatientList* last = NULL;

    if (head == NULL) {
        return;
    }

    do {
        swapped = 0;
        pat = head;

        while (pat->next != last) {
            if (compare(pat->data, pat->next->data) > 0) {
                swapPatients(pat, pat->next);
                swapped = 1;
            }
            pat = pat->next;
        }
        last = pat;
    } while (swapped);
}

int compare(PatientRecord* patient1, PatientRecord* patient2) {
    if (patient1->arrivalDate < patient2->arrivalDate) {
        return -1;
    } else if (patient1->arrivalDate > patient2->arrivalDate) {
        return 1;
    } else {
        if (patient1->arrivalTime < patient2->arrivalTime) {
            return -1;
        } else if (patient1->arrivalTime > patient2->arrivalTime) {
            return 1;
        } else {
            return 0;
        }
    }
}


//////////////////////////////////////////////////////////////////////////////////////////
//Valentina von Main

void printOutMap(Seat seatingMap[MAP_ROWS][MAP_COLUMNS]) {
    printf("  Seating Map\n\n");

    for (int i = 0; i < MAP_ROWS; i++) {
        printf("------------------------------\n|");
        for (int j = 0; j < MAP_COLUMNS; j++) {
            if (seatingMap[i][j].isReserved) {
                printf("  X | ");
            } else {
                printf(" %2d | ", seatingMap[i][j].seatNumber);
            }
        }
        printf("\n");
    }
    printf("------------------------------\n|");
}

/*
void printOutMap(int (*seatingMap)[MAP_ROWS]){

    printf("  Seating Map\n\n"); 

    for (int i = 0; i < MAP_ROWS; i++) {
        printf("------------------------------\n|");
        for (int j = 0; j < MAP_COLUMNS; j++) {
            if(seatingMap[i][j] == 0){          //if 0, seat number is occupied -> print X
                printf("  X | ");
            }
            else{ 
            printf(" %2d | ", seatingMap[i][j]);
            }
        }
        printf("\n");
    }
    printf("------------------------------\n|");
}
*/


void initializeSeatingMap(Seat seatingMap[MAP_ROWS][MAP_COLUMNS]) {
    int seatNumber = 1;
    for (int i = 0; i < MAP_ROWS; i++) {
        for (int j = 0; j < MAP_COLUMNS; j++) {
            seatingMap[i][j].seatNumber = seatNumber++;
            seatingMap[i][j].isReserved = false;
        }
    }
}

bool reserveSeatByNumber(int seatNumber, Seat seatingMap[MAP_ROWS][MAP_COLUMNS]) {
    for (int i = 0; i < MAP_ROWS; i++) {
        for (int j = 0; j < MAP_COLUMNS; j++) {
            if (seatingMap[i][j].seatNumber == seatNumber) {
                if (!seatingMap[i][j].isReserved) {
                    seatingMap[i][j].isReserved = true;
                    return true;
                }
                break;
            }
        }
    }
    return false;
}

bool cancelReservationByNumber(int seatNumber, Seat seatingMap[MAP_ROWS][MAP_COLUMNS]) {
    for (int i = 0; i < MAP_ROWS; i++) {
        for (int j = 0; j < MAP_COLUMNS; j++) {
            if (seatingMap[i][j].seatNumber == seatNumber) {
                if (seatingMap[i][j].isReserved) {
                    seatingMap[i][j].isReserved = false;
                    return true;
                }
                break;
            }
        }
    }
    return false;
}
int isNumericInput(const char *str) {
    // Überprüfen, ob jedes Zeichen in der Zeichenkette eine Ziffer ist
    for (size_t i = 0; i < strlen(str); i++) {
        if (!isdigit(str[i])) {
            return 0; // Rückgabewert 0 bedeutet, dass die Zeichenkette keine gültige Zahl ist
        }
    }
    return 1; // Rückgabewert 1 bedeutet, dass die Zeichenkette nur aus Zahlen besteht
}

void reserveSeatsFromPatientList(PatientList* patientList, Seat seatingMap[MAP_ROWS][MAP_COLUMNS]) {
    PatientList *currentPatientNode = patientList;

    //loop through list
    while (currentPatientNode != NULL) {
        int seatNumber = currentPatientNode->data->seatingNumber;
        
        //check that the seat number is greater than 0 and does not exceed the total number of seats
        if (seatNumber > 0 && seatNumber <= MAP_ROWS * MAP_COLUMNS && currentPatientNode->data->departureDate == 0) {
            //reserve seat
            reserveSeatByNumber(seatNumber, seatingMap);
        }
        
        //next patient
        currentPatientNode = currentPatientNode->next;
    }
}


unsigned long getSSNfromUser() {
    unsigned long ssn = 0;
    int validCheck = 0;
    char buffer[20];

    while (validCheck < 10) {
        printf("Please enter the patient's social security number (FORMAT: 0000YYMMDD)\n");
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            buffer[strcspn(buffer, "\n")] = '\0'; // Zeilenumbruch entfernen

            if (!isNumericInput(buffer)) {
                printf("Invalid input! Please only use numbers.\n");
                validCheck++;
            } else if (strlen(buffer) != 10) {
                printf("Invalid input! Please only use 10 digits!\n");
                validCheck++;
            } else {
                char *endptr;
                ssn = strtoul(buffer, &endptr, 10);

                // Überprüfen, ob alle Zeichen in der Eingabe erfolgreich konvertiert wurden
                if (endptr == buffer || *endptr != '\0') {
                    printf("Invalid input! Please try again.\n");
                    validCheck++;
                } else {
                    validCheck = 10;
                }
            }
        } else {
            printf("Error reading input.\n");
            return 0;
        }
    }
    return ssn;
}

//maybe some splitting up would be nice haha :(
int addNewPatient(Seat seatingMap[MAP_ROWS][MAP_COLUMNS]) {
    PatientRecord tempPatient = {0, "x", 0,0,0,0, 'N'};
    unsigned long ssn = getSSNfromUser();
    if (ssn == 0) {
        printf("Error: Invalid social security number.\n");
        return 1;
    }
    tempPatient.ssn = ssn;
    int checkDefault=0;

    printf("\nPlease enter the patients name (FORMAT: Surname Forename)\n");
    fgets(tempPatient.name, MAX_PATIENT_NAME, stdin);
    tempPatient.name[strcspn(tempPatient.name, "\n")] = 0; // Remove newline character from the string

    int attempts = 0;
    printf("\nIs the patient infectious? [Y/N]\n");
    while (1) {
        char c = getchar();
        if (getchar() != '\n') {
            while (getchar() != '\n'); // discard extra characters
        }
        switch (tolower(c)) {
            case 'y':
                tempPatient.infectious = 'Y';
                break;
            case 'n':
                tempPatient.infectious = 'N';
                break;
            default:
                attempts++;
                if (attempts >= 3) {
                    printf("Invalid input entered too many times. Exiting...\n");
                    return -1;
                }
                printf("Invalid input! Please enter 'Y' or 'N':\n");
                continue;
        }
        break;
    }



    printf("\nPlease press 'a' if the patient came by ambluance or 'o' if they came by themself\n");
    while (1) {
        char c = getchar();
        if (getchar() != '\n') {
            while (getchar() != '\n');
        }
        switch (tolower(c)) {
            case 'a':
                tempPatient.seatingNumber = -1;
                printf("Patient by ambulance - saved!\n");
                break;
            case 'o':
                

                tempPatient.arrivalTime = getTime();
                tempPatient.arrivalDate = getDate();

                // TO DO: check if seat is already taken
                printf("\nPlease enter the seating number (1-%d):\n", MAP_ROWS * MAP_COLUMNS);
                    while (1) {
                        int result = scanf("%d", &tempPatient.seatingNumber);
                        while (getchar() != '\n'); // discard extra characters

                        if (result == 1 && tempPatient.seatingNumber >= 1 && tempPatient.seatingNumber <= (MAP_ROWS * MAP_COLUMNS)) {
                            if (reserveSeatByNumber(tempPatient.seatingNumber, seatingMap) == false) {
                                printf("Seat %d is already taken! Please enter another seating number (1-%d):\n", tempPatient.seatingNumber, MAP_ROWS * MAP_COLUMNS);
                            } else {
                                reserveSeatByNumber(tempPatient.seatingNumber, seatingMap);
                                break;
                            }
                        } else {
                            printf("Invalid input! Please enter a valid seating number between 1 and %d:\n", MAP_ROWS * MAP_COLUMNS);
                        }
                    }
                printf("Patient came by themself - saved!\n");
                break;
            default:
                checkDefault++;
                if (checkDefault > 10) {
                    printf("Your input could not be processed for the %dth time...\n"
                           "closing adding new patient...\n\n\n", checkDefault);
                    return -1;
                }
                printf("Your input could not be processed! Please enter only one character\n\n");
                continue;
        }
        break;
    }
    M_WRITEPATIENTDATASTRUCT((&tempPatient));

/*TESTPRINT*/
    printf("Saved Patient Record:\n"
       "SSN: %lu | Name: %s | Arrival Time: %d | Arrival Date: %ld | Infectious: %c | Seating Number: %d\n",
        tempPatient.ssn, tempPatient.name, tempPatient.arrivalTime, tempPatient.arrivalDate,
        tempPatient.infectious, tempPatient.seatingNumber);

    return 0;
}



int menu(Seat seatingMap[MAP_ROWS][MAP_COLUMNS], PatientList *head) {
    int static checkDefault = 0;
    PatientList *prio = (PatientList *)malloc(sizeof(PatientList));
    PatientList *wait = (PatientList *)malloc(sizeof(PatientList));
    PatientList *patNeighbours = (PatientList *)malloc(sizeof(PatientList));
    PatientRecord *pat = (PatientRecord*) malloc(sizeof(PatientRecord));
    unsigned long ssn = 0;
    while (1) {
        
        
        printf("You are now in the menu...\n"
               "\t- Press 'n' to create a new patient\n"
               "\t- Press 'p' to display the prioritization list\n"
               "\t- Press 'w' to display the waiting area list\n"
               "\t- Press 'c' to change the infectious status of a patient\n"
               "\t- Press 'i' to display infectious patients incl. seat neighbors\n"
               "\t- Press 's' to display the current seating arrangements\n"
               "\t- Press 't' to remove of a patient through successful treatment\n"
               "\t- Press 'q' to close the program\n");

        int c = getchar();
        if (getchar() != '\n') {
            while (getchar() != '\n'); // to catch all characters if user enters too many
        }

        switch (c) {
            /***Create new patient***/
            case 'n':
                if(addNewPatient(seatingMap) == 0) printf("patient saved successfully!\n");
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
                if (ssn == 0) {
                    printf("Error: Invalid social security number.\n");
                    
                } 
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
                    printPatientList(wait,WHOLE);
                }
                break;
            /***Display infectious patients incl. seat neighbors***/
            case 'i':
                printf("Seat neighbors of infectious patient\n");
    //TEST with 5678901111
                ssn = getSSNfromUser();
                if (ssn == 0) {
                    printf("Error: Invalid social security number.\n");
                    
                } 
                else {
                patNeighbours = getSeatNeighbour(head, ssn);
                printPatientList(patNeighbours, WHOLE);
                ssn = 0;
                }
                break;
            /***Display the current seating arrangements***/
            case 's':
                printOutMap(seatingMap);
                break;
            /***Removal of a patient through successful treatment***/
            case 't':
    //TEST mit 1234566778
                
                ssn = getSSNfromUser();
                if (ssn == 0) {
                    printf("Error: Invalid social security number.\n");
                    
                } 
                else {
                addDeparture(head, ssn);
                pat = findPatient(head,ssn);
                cancelReservationByNumber(pat->seatingNumber, seatingMap);
                printf("successful treatment of patient saved in database!\n\n");
                }
                
                break;
            /***Close program***/
            case 'q':
                printf("You chose to close the program ... bye!\n\n");
                
                return 1;
            /***Default: Wrong input -> entering again menu***/
            default:
                checkDefault++;
                if (checkDefault > 10) {
                    printf("Your input could not be processed for the %dth time...\n"
                           "closing program, bye!!!\n\n\n", checkDefault);
                    return -1;
                }
                printf("Your input could not be processed! Please enter only one character\n\n");
                continue;
        }
    }
}


void printErrorMsg(int error_code) {
    switch (error_code)
    {
    case ERR_CLOSING_FILE:
        fprintf(stderr,"An error occurred while closing a file\n");
        return;
    case ERR_OPENING_FILE:
    fprintf(stderr,"An error occurred while opening a file\n");
        return ;
    case ERR_MALLOC:
    fprintf(stderr,"Error allocating memory\n");
        return;
    fprintf(stderr,"No error message was found\n");
    return ;
    case ERR_WCSV_CLOSING_CSV_FILE:
    fprintf(stderr,"ERROR WriteCSV: the file could not be closed\n");
    return;
    case ERR_WCSV_OPENING_CSV_FILE:
    fprintf(stderr,"ERROR WriteCSV: the file could not be opened\n");
    return;
    case ERR_WCSV_CONVERTING_INT_TO_STRING:
    fprintf(stderr,"ERROR WriteCSV: the int could not be converted to a string\n");
    return;
    case ERR_WCSV_GENERATING_WRITE_STRING:
    fprintf(stderr,"ERROR WriteCSV: the write string could not be successfully generated\n");
    return;


          default:
          fprintf(stderr,"An Unknown Error has occured!\n");
            return;
    }
}