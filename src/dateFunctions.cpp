#include "../include/dateFunctions.h"
#include <time.h>

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