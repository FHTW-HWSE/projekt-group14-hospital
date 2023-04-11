#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H


#define MAX_FILE_SIZE 1000

char* read_csv(const char* filename);
void write_csv(const char* filename, const char* data);

#endif