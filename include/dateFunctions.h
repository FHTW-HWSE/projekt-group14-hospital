#pragma once

#include "../include/definitions.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//format of date/time
//iso 8601: YYYY-MM-DDThh:mm:ss, fff

int getTime(struct tm *timeInfo);
long getDate();
PatientRecord* searchPatientInCSV(unsigned long ssn);

/*
time_t convertStringToDatetime(char * text);
char * convertDatetimeToString(time_t timestamp);*/