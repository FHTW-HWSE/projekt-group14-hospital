#include <stdio.h>
#include <stdlib.h>
#include "file_handling.h"


int main (int argc, char *argv[]){

 char* csv_content;
    
    // call read_csv-function and safe string 
    csv_content = read_csv("test.csv");
    
    if (csv_content == NULL) {
        printf("Error reading file\n");
        return 1;
    }
    
    // print contant of CSV
    printf("CSV-content:\n%s\n", csv_content);
    
    // free allocated memory
    free(csv_content);

    return 0;
}

