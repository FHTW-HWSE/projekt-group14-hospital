#include <catch2/catch.hpp>
#include <dateFunctions.h>

TEST_CASE("Time_returned_in_hhmm_format_as_int") {
    int test=0, time=0;
    long date=0;
    
    time = getTime();
    date = getDate();

    REQUIRE(time <= 2400 && time >= 0000);
    REQUIRE(date <= 99991231 && date >= 00000101);
}