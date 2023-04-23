#include "../include/CSV_write.h"
#define CONFIG_CATCH_CSV_WRITE
#include <catch2/catch.hpp>
#include <stdbool.h>

const char* PATH_TO_PATIENT_DATA_CSV_FILE = "../programFiles/PatientData/PatientDataDB.csv";

int writePatientData(unsigned int SocialSecurityNumber, char PatientName[MAX_PATIENT_NAME], long ArrivalDateTime,
                    long DepartureDateTime,char Infectious, unsigned short int seatingNumber,short mode){

bool markerFileWasCreated = false;


char ArrivalDateTimeStr[MAX_DATE_TIMESTRING_LENGTH];
 char DepartureDateTimeStr[MAX_DATE_TIMESTRING_LENGTH];


//convert int to string area
//untested!!
int result = snprintf(ArrivalDateTimeStr, MAX_DATE_TIMESTRING_LENGTH, "%ld", ArrivalDateTime);
if (result < 0 || result >= MAX_DATE_TIMESTRING_LENGTH) {
  fprintf(stderr,"\nERROR Converting int to string!\nError ID: %l\n", E_CONVERTING_INT_TO_STRING);
        return -1;
}

result = snprintf(DepartureDateTimeStr, MAX_DATE_TIMESTRING_LENGTH, "%ld", DepartureDateTime);
if (result < 0 || result >= MAX_DATE_TIMESTRING_LENGTH) {
  fprintf(stderr,"\nERROR Converting int to string!\nError ID: %l\n", E_CONVERTING_INT_TO_STRING);
        return -1;
}

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

//so output is correctly formatted even if Manually entered entry doesn't contain \n
 // Check if the last line is empty
    fseek(file, -1, SEEK_END);
    int lastChar = fgetc(file);
    if (lastChar != '\n') {
        // If the last line is not empty, add a new line before writing data
        fprintf(file, "\n");
    }

// ########  Print into File     ####################
    //hu is unsigned short int
    fprintf(file, "%u,%s,%s,%s,%c,%hu\n", SocialSecurityNumber, PatientName, ArrivalDateTimeStr, DepartureDateTimeStr, Infectious, seatingNumber);

                  

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

/*
to main for testing

//michi
writePatientData(332146, "Hans", "19:00", "20:00", 'Y', 7);
return 0;
//michi end 





//michi
struct tm *testTimeStruct;
int time1 ;
time_t now2;
 time(&now2);
 testTimeStruct = localtime(&now2);
 time1 = getTime(testTimeStruct);
printf("This is The time: %d !\n",time1);
//writePatientData(332146, "Hans", getTime(testTimeStruct), getTime(testTimeStruct), 'Y', 7);
return 0;

*/




/*
FIZZBUZ examle code

SCENARIO("FizzBuzz Specification") 
{
  GIVEN("A number that is divisible by three and not by five") 
  {
    auto const number = GENERATE(3, 6, 9, 42, 3003);
    WHEN("its FizzBuzz representation is calculated") 
    {
      auto const result = fizzbuzz(number);
      THEN("the result is 'Fizz'") 
      { 
        REQUIRE(result == "Fizz"); 
      }
    }
  }

  */