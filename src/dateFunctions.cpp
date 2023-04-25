#include "../include/dateFunctions.h"
#include "../include/definitions.h"

/**
 * @brief Calculates the time in the format hhmm as an integer.
 *
 * @param timeInfo Pointer to a struct tm containing the time information.
 *
 * @return The time in the format hhmm as an integer, or -1 if timeInfo is a null pointer.
 */

int getTime(struct tm *timeInfo) {
     
     if (timeInfo == NULL) {
        return -1;
    }
    int hour, minute, result;
        
    hour = timeInfo->tm_hour;
    minute = timeInfo->tm_min;
    
    hour = hour*100;

    result = hour+minute;

    return result; //hhmm
}




long getDate() {
    time_t now;
    struct tm *timeInfo;
    long date=0;
    int year, month, day;

    time(&now);
    timeInfo = localtime(&now);
    year = timeInfo->tm_year; //year since 1900
    month = timeInfo->tm_mon; //month 0-11
    day = timeInfo->tm_mday; //day

    year=(year+1900)*10000;
    month=(month+1)*100;

    date = year+month+day;

    return date; //yyyymmdd
}

PatientRecord* searchPatientInCSV(unsigned long ssn) {
  FILE* fp = fopen("../programFiles/PatientData/PatientDataDB.csv", "r");
  if (fp == NULL) {
    printf("Error: Could not open file ../programFiles/PatientData/PatientDataDB.csv\n");
    return NULL;
  }

  char line[100];
  PatientRecord* patient = NULL;
  while (fgets(line, sizeof(line), fp) != NULL) {
    char* ssnStr = strtok(line, ",");
    if (ssn == atol(ssnStr)) {
      patient = (PatientRecord*) malloc(sizeof(PatientRecord));
      patient->ssn = ssn;

      char* name = strtok(NULL, ",");
      strcpy(patient->name, name);

      char* arrivalTimeStr = strtok(NULL, ",");
      patient->arrivalTime = atoi(arrivalTimeStr);

      char* arrivalDateStr = strtok(NULL, ",");
      patient->arrivalDate = atol(arrivalDateStr);

      char* departureTimeStr = strtok(NULL, ",");
      patient->departureTime = atoi(departureTimeStr);

      char* departureDateStr = strtok(NULL, ",");
      patient->departureDate = atol(departureDateStr);

      char* infectiousStr = strtok(NULL, ",");
      patient->infectious = infectiousStr[0];

      char* seatingNumberStr = strtok(NULL, ",");
      patient->seatingNumber = atoi(seatingNumberStr);

      break;
    }
  }

  fclose(fp);
  return patient;
}