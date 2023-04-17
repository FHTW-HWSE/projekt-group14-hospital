#include "../include/CSV_write.h"
#define CONFIG_CATCH_CSV_WRITE
#include <catch2/catch.hpp>
 


int writePatientData(unsigned int SocialSecurityNumber, char PatientName[MAX_PATIENT_NAME], int ArrivalTime,
                    int DepartureTime,char Infectious, unsigned short int seatingNumber){



char ArrivalTimeStr[MAX_TIMESTRING_LENGTH];
 char DepartureTimeStr[MAX_TIMESTRING_LENGTH];


//convert int to string area
//untested!!
int result = snprintf(ArrivalTimeStr, MAX_TIMESTRING_LENGTH, "%i", ArrivalTime);
if (result < 0 || result >= MAX_TIMESTRING_LENGTH) {
  fprintf(stderr,"\nERROR Converting int to string!\nError ID: %i\n", E_CONVERTING_INT_TO_STRING);
        return -1;
}

result = snprintf(DepartureTimeStr, MAX_TIMESTRING_LENGTH, "%i", DepartureTime);
if (result < 0 || result >= MAX_TIMESTRING_LENGTH) {
  fprintf(stderr,"\nERROR Converting int to string!\nError ID: %i\n", E_CONVERTING_INT_TO_STRING);
        return -1;
}

    // Opening File Stream
    //r+ so can also read from the file if last entery is newling
    FILE *file = fopen("../programFiles/PatientData/test.csv", "r+");


    // Error Handeling if file could not be opened
    if (file == NULL){
        fprintf(stderr,"\nERROR opening the CSV File\nError ID: %i\n", E_OPENING_CSV_FILE);
        return -1;
    }

 // Check if the last line is empty
    fseek(file, -1, SEEK_END);
    int lastChar = fgetc(file);
    if (lastChar != '\n') {
        // If the last line is not empty, add a new line before writing data
        fprintf(file, "\n");
    }

    //hu is unsigned short int
    fprintf(file, "%u,%s,%s,%s,%c,%hu\n", SocialSecurityNumber, PatientName, ArrivalTimeStr, DepartureTimeStr, Infectious, seatingNumber);

                  

    // Closing the file Stream and error handeling
    if (fclose(file)){
        fprintf(stderr,"\nERROR closing the CSV-File\nError ID: %i\n", E_CLOSING_CSV_FILE);
        return -1;
    }


    return 0;
}  //End WriteParameterData Function

/*
to main for testing

//michi
writePatientData(332146, "Hans", "19:00", "20:00", 'Y', 7);
return 0;
//michi end 



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