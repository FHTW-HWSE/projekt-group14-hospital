
#include <catch2/catch.hpp>
#include "../include/dateFunctions.h"

TEST_CASE("Time_returned_in_hhmm_format_as_int") {
    int result = getTime();

    REQUIRE(result <= 2359 && result >=0);
}

TEST_CASE("Time_returned_in_yyyymmdd_format_as_int") {
    int result = getDate();

    REQUIRE(result <= 99991231 && result >=20230101);
}