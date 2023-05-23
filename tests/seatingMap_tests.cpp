#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "../include/otherfunctions.h"

TEST_CASE( "Testing reserveSeatByNumber function", "[reserveSeatByNumber]" ) {
    //seating map for testing
    Seat seatingMap[MAP_ROWS][MAP_COLUMNS];
    initializeSeatingMap(seatingMap);

    SECTION("Reserve an available seat") {
        REQUIRE(reserveSeatByNumber(1, seatingMap) == true);
        REQUIRE(seatingMap[0][0].isReserved == true);  //Seat #1 should now be reserved
    }

    SECTION("Reserve a seat that is already reserved") {
        reserveSeatByNumber(1, seatingMap);
        REQUIRE(reserveSeatByNumber(1, seatingMap) == false);  //should fail because seat 1 is already reserved
    }

    SECTION("Try to reserve a seat with invalid number") {
        REQUIRE(reserveSeatByNumber(0, seatingMap) == false);  //should fail because 0 is an invalid seat number
        REQUIRE(reserveSeatByNumber(MAP_ROWS * MAP_COLUMNS + 1, seatingMap) == false);  //should fail because this seat number is out of bounds
    }
}

TEST_CASE( "Testing cancelReservationByNumber function", "[cancelReservationByNumber]" ) {
    //seating map for testing
    Seat seatingMap[MAP_ROWS][MAP_COLUMNS];
    initializeSeatingMap(seatingMap);

    SECTION("Cancel a reserved seat") {
        reserveSeatByNumber(1, seatingMap);
        REQUIRE(cancelReservationByNumber(1, seatingMap) == true);
        REQUIRE(seatingMap[0][0].isReserved == false);  //seat 1 should now no longer be reserved
    }

    SECTION("Try to cancel a seat that is not reserved") {
        REQUIRE(cancelReservationByNumber(1, seatingMap) == false);  //should fail, because seat 1 is not reserved
    }

    SECTION("Try to cancel a seat with invalid number") {
        REQUIRE(cancelReservationByNumber(0, seatingMap) == false);  //should fail because 0 is an invalid seat number
        REQUIRE(cancelReservationByNumber(MAP_ROWS * MAP_COLUMNS + 1, seatingMap) == false);  //should fail because this seat number is out of bounds
}
}
