#include <stdio.h>
#include <stdlib.h>
#include "../include/file_handling.h"

enum ERROR_CODES {
    ERRORCODE1 = 3265,
    ERRORCODE2 = 3245,
};


int main (int argc, char *argv[]){

//michi auskommentiert weil es bei mir nicht compitlet
//char buffer[1000] = {0};
char * buffer = (char*)malloc(sizeof(char)*1000);

buffer = read_csv("test.csv");

printf("%s", buffer);

    return 0;
}

