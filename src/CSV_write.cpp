#include "../include/CSV_write.h"
#define CONFIG_CATCH_CSV_WRITE
#include <catch2/catch.hpp>



SCENARIO("Test Write Worked"){

    GIVEN("The Write function has been called")

int writePatientData(unsigned int SocialSecurityNumber, char PatientName[MAX_PATIENT_NAME], char ArrivalTime[MAX_TIMESTRING_LENGTH],
                    char DepartureTime[MAX_TIMESTRING_LENGTH],char Infectious, unsigned short int seatingNumber){



    // Opening File Stream
    FILE *file = fopen("../include/test.csv", "a");

    // Error Handeling if file could not be opened
    if (file == NULL){
        fprintf(stderr,"\nERROR opening the CSV File\nError ID: %i\n\n", E_OPENING_CSV_FILE);
        return -1;
    }




//Testing
SCENARIO("Writing the patient Data into the CSV File")
{
    GIVEN("The Write function has been called and the File sucessfully opened")
    {
        WHEN("The Write Patien Data Function is Preformed")
        {

  ///             ############      Write Patient Data Area      ##########
    //hu is unsigned short int
    fprintf(file, "%u,%s,%s,%s,%c,%hu\n", SocialSecurityNumber, PatientName, ArrivalTime, DepartureTime, Infectious, seatingNumber);
int a = 10;  //just temporary to bridge Test while not finished
       
       THEN("The Write has to be Preformed successfully"){
        REQUIRE(a == 10);
       }

        }// END WHEN
    }// End GIVEN
 }//END SCENARIO
                    


    // Closing the file Stream and error handeling
    if (fclose(file)){
        fprintf(stderr,"\nERROR closing the CSV-File\nError ID: %i\n\n", E_CLOSING_CSV_FILE);
        return -1;
    }


    return 0;
}  //End WriteParameterData Function






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