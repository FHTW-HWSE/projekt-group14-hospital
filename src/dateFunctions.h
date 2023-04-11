#pragma once

#include <time.h>

//format of date/time
//iso 8601: YYYY-MM-DDThh:mm:ss, fff

time_t convertStringToDatetime(char * text);
char * convertDatetimeToString(time_t timestamp);