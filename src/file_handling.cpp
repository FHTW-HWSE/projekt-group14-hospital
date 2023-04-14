
/**
 * @file file_handling.c
 * @brief A program to read the contents of a CSV file into a string
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/file_handling.h"


/**
 * @brief Reads the contents of a CSV file into a string
 *
 * @param[in] filename The name of the CSV file to read
 *
 * @return A string containing the contents of the CSV file
 */
char* read_csv(const char* filename) {
    FILE* fp;
    char* buffer;
    long file_size;
    
    // Open the file for reading
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file %s\n", filename);
        return NULL;
    }
    
    // Determine the size of the file
    fseek(fp, 0, SEEK_END);
    file_size = ftell(fp);
    rewind(fp);
    
    // Allocate memory for the buffer
    buffer = (char*)malloc(file_size + 1);
    if (buffer == NULL) {
        printf("Error allocating memory\n");
        fclose(fp);
        return NULL;
    }
    
    // Read the contents of the file into the buffer
    fread(buffer, sizeof(char), file_size, fp);
    buffer[file_size] = '\0';
    
    // Close the file
    if(fclose(fp) != 0){
        printf("Error closing file %s", filename);
        return NULL;
    }
    
    return buffer;
}



/**
 * @brief Writes a string to a CSV file
 *
 * @param[in] filename The name of the CSV file to write
 * @param[in] data The string to write to the file
 */
void write_csv(const char* filename, const char* data) {
    FILE* fp;
    
    // Open the file for writing
    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }
    
    // Write the data to the file
    fputs(data, fp);
    
     // Close the file
    if(fclose(fp) != 0){
        printf("Error closing file %s", filename);
        return ;
    }
}
