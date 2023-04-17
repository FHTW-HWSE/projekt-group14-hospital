#pragma once

#include <time.h>

//format of date/time
//iso 8601: YYYY-MM-DDThh:mm:ss, fff

int getTime();
long getDate();

/*
time_t convertStringToDatetime(char * text);
char * convertDatetimeToString(time_t timestamp);*/