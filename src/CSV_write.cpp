#include "../include/CSV_write.h"
#define CONFIG_CATCH_CSV_WRITE
#include <catch2/catch.hpp>
#include <stdbool.h>

const char* PATH_TO_PATIENT_DATA_CSV_FILE = "../programFiles/PatientData/PatientDataDB.csv";

int writePatientData(unsigned long SocialSecurityNumber, char PatientName[MAX_PATIENT_NAME], int arrivalTime, long arrivalDate,
                    int departureTime,long departureDate,char Infectious, unsigned short int seatingNumber,short mode){

bool markerFileWasCreated = false;



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
    fprintf(file, "%lu,%s,%i,%l,%i,%l,%c,%hu\n", SocialSecurityNumber, PatientName, arrivalDate, arrivalTime, departureDate, departureTime, Infectious, seatingNumber);

                  

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