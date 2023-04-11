#include <stdio.h>
#include <stdlib.h>
#include "file_handling.h"


int main (int argc, char *argv[]){

char buffer[1000] = {0};

buffer = read_csv("test.csv");

printf("%s", buffer);

    return 0;
}

