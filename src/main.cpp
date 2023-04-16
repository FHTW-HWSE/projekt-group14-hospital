#include <stdio.h>
#include <stdlib.h>
#include "../include/CSV_read.h"
#include "../include/CSV_write.h"
#include <catch2/catch.hpp>

enum ERROR_CODES {
    ERRORCODE1 = 3265,
    ERRORCODE2 = 3245,
};


int main (int argc, char *argv[]){



//char buffer[1000] = {0};
char * buffer = (char*)malloc(sizeof(char)*1000);

buffer = read_csv("test.csv");

printf("%s", buffer);

    return 0;
}

