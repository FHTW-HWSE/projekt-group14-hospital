#include "../include/CSV_write.h"
#define CONFIG_CATCH_CSV_WRITE
#include <catch2/catch.hpp>
#include <stdbool.h>

// Write 
//TODO case first entry to db so no new \n at start of file

const char* PATH_TO_PATIENT_DATA_CSV_FILE = "../programFiles/PatientData/PatientDataDB.csv";

#pragma region Helper Functions
// helper function to generate the string to write to the file
// for easier testing
char * generate_Write_String(unsigned long SocialSecurityNumber, char PatientName[MAX_PATIENT_NAME], int arrivalTime, long arrivalDate,
                    int departureTime,long departureDate,char Infectious,int seatingNumber){
  char * writeString = (char*)malloc(1000*sizeof(char));
  sprintf(writeString, "%lu,%s,%i,%i,%i,%i,%c,%i\n",
    SocialSecurityNumber,
     PatientName,
      arrivalTime,
       arrivalDate,
        departureTime,
         departureDate,         
           Infectious,
            seatingNumber
            );
  return writeString;
}

// helper function to write a write string to the file
void write_String_To_File(char * writeString){
  FILE *file = fopen(PATH_TO_PATIENT_DATA_CSV_FILE, "a");
//  fprintf(file, "%s", writeString);
  fputs(writeString, file); // used puts so automatically uses \n
  fclose(file);
}
#pragma endregion Helper Functions

int writePatientData(unsigned long SocialSecurityNumber, char PatientName[MAX_PATIENT_NAME], int arrivalTime, long arrivalDate,
                    int departureTime,long departureDate,char Infectious,int seatingNumber){


//marker for if a new file was created
bool markerFileWasCreated = false;

//opening the file and checking if it exists
#pragma region File Opening
//Testing if Requested File existes, if not creating it
FILE * TestFileOpen = fopen(PATH_TO_PATIENT_DATA_CSV_FILE, "r");
//if file doesnt exist create it 
if (TestFileOpen == NULL){
  #if DEBUG_MESSAGES_WRITE_CSV 
  printf("Status writing Patient Data: No existing database, databse was created at %s!\n",PATH_TO_PATIENT_DATA_CSV_FILE);
  #endif
  TestFileOpen = fopen(PATH_TO_PATIENT_DATA_CSV_FILE, "w");
  fclose(TestFileOpen);
} else {
fclose(TestFileOpen);
}



    // Opening File Stream
    //r+ so can also read from the file if last entery is newling
    FILE *file = fopen(PATH_TO_PATIENT_DATA_CSV_FILE, "r+");


    // Error Handeling if file could not be opened
    if (file == NULL){
        fprintf(stderr,"\nERROR opening the CSV File\nError ID: %i\n", E_OPENING_CSV_FILE);
        return -1;
    }
#pragma endregion File Opening

//forrmatting the file so the enteries are allways stored in the same format
#pragma region File Formatting
  //var for formatting function
  int lastChar;


    //check if the file is empty to skipp the following formatting code
    char test = getc(file);
    if (test == EOF){
      fseek(file, -1, SEEK_CUR);
      goto skippedFormating;
    } else {
      fseek(file, -1, SEEK_CUR);
    }


// FORMATTING FUNCTION
//so output is correctly formatted even if Manually entered entry doesn't contain \n
 // Check if the last line is empty
    fseek(file, -1, SEEK_END);
     lastChar = fgetc(file);
    if (lastChar != '\n') {
        // If the last line is not empty, add a new line before writing data
        fprintf(file, "\n");
    }

//label to skip the formatting code if the file is empty
skippedFormating:
#pragma endregion File Foramtting

//chosing Actions depending on the chosen mode

#pragma region File Writing

//old way to write without unit test
#if 0

 old way to write without unit test
  // ########  Print into File     ####################
    //hu is unsigned short int
    fprintf(file, "%lu,%s,%i,%i,%i,%i,%c,%i\n",
    SocialSecurityNumber,
     PatientName,
      arrivalTime,
       arrivalDate,
        departureTime,
         departureDate,         
           Infectious,
            seatingNumber
            );
#endif

//new way to write with unit test
//generate the string to write to the file
char * writeString = generate_Write_String(SocialSecurityNumber, PatientName, arrivalTime, arrivalDate, departureTime, departureDate, Infectious, seatingNumber);
if(writeString == NULL){
  fprintf(stderr,"\nERROR generating the write string\nError ID: %i\n", E_GENERATING_WRITE_STRING);
  return -1;
}



//writing the string to the file
write_String_To_File(writeString);

      //freeing the memory of the write string to avoid memory leaks
free(writeString);            

    // Closing the file Stream and error handling
    if (fclose(file)){
        fprintf(stderr,"\nERROR closing the CSV-File\nError ID: %i\n", E_CLOSING_CSV_FILE);
        return -1;
    }

    //Defined Return value as 2 if a new file was created and the function finished successfully
    if(markerFileWasCreated){
      return 2;
    }


    return 0;
}  //End WriteParameterData Function


