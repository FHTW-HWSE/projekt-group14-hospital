#include <catch2/catch.hpp>
#include <fizzbuzz.h>

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

  GIVEN("A number that is divisible by five and not by three") {
    auto const number = GENERATE(5, 10, 20, 500, 5005);
    WHEN("its FizzBuzz representation is calculated") {
      auto const result = fizzbuzz(number);
      THEN("the result is 'Buzz'") { REQUIRE(result == "Buzz"); }
    }
  }

  GIVEN("A number that is divisible by both three and five") {
    auto const number = GENERATE(15, 30, 45, 300, 3000, 6000);
    WHEN("its FizzBuzz representation is calculated") {
      auto const result = fizzbuzz(number);
      THEN("the result is 'FizzBuzz'") { REQUIRE(result == "FizzBuzz"); }
    }
  }

  GIVEN("A number that is divisible by neither three nor five") {
    auto const number = GENERATE(0, 1, 2, 4, 7, 8, 4711);
    WHEN("its FizzBuzz representation is calculated") {
      auto const result = fizzbuzz(number);
      THEN("the result is the number's string representation") {
        REQUIRE(result == std::to_string(number));
      }
    }
  }

  GIVEN("Any negative number") {
    auto const number = GENERATE(-1, -3, -5, -15, -4711);
    WHEN("its FizzBuzz representation is calculated") {
      auto const result = fizzbuzz(number);
      THEN("the result is the number's string representation") {
        REQUIRE(result == std::to_string(number));
      }
    }
  }
}