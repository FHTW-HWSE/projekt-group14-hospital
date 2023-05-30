#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <stdio.h>
#include <stdbool.h>
#include "../include/otherfunctions.h"

TEST_CASE("Test isNumericInput function", "[isNumericInput]") {
    SECTION("Valid numeric input") {
        const char* testString = "12345";
        bool result = isNumericInput(testString);
        REQUIRE(result == true);
    }

    SECTION("Invalid non-numeric input") {
        const char* testString = "abcd23";
        bool result = isNumericInput(testString);
        REQUIRE(result == false);
    }
}

TEST_CASE("Test isValidSSN function", "[isValidSSN]") {
    SECTION("Valid SSN") {
        const char* testString = "1234567890";
        bool result = isValidSSN(testString);
        REQUIRE(result == true);
    }

    SECTION("Invalid SSN - incorrect length") {
        const char* testString = "123456789";
        bool result = isValidSSN(testString);
        REQUIRE(result == false);
    }

    SECTION("Invalid SSN - non-numeric characters") {
        const char* testString = "a1b234c56";
        bool result = isValidSSN(testString);
        REQUIRE(result == false);
    }
}

TEST_CASE("Test convertSSN function", "[convertSSN]") {
    SECTION("Valid SSN") {
        const char* testString = "1234567890";
        unsigned long result = convertSSN(testString);
        REQUIRE(result == 1234567890);
    }

    SECTION("Invalid SSN - non-numeric characters") {
        const char* testString = "abc123456";
        unsigned long result = convertSSN(testString);
        REQUIRE(result == 0);
    }

    SECTION("Invalid SSN - invalid format") {
        const char* testString = "1234a56789";
        unsigned long result = convertSSN(testString);
        REQUIRE(result == 0);
    }
}
