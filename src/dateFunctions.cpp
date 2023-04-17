#include "../include/dateFunctions.h"
#include <time.h>


int getTime(struct tm *timeInfo) {
    
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