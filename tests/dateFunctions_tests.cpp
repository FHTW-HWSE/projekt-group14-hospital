
#include <catch2/catch.hpp>
#include ../include/dateFunctions.h"

TEST_CASE("Time_returned_in_hhmm_format_as_int") {
    int test=0, time=0;
   // long date=0;
    struct tm timeInfo = {0};

    timeInfo.tm_hour = 12;
    timeInfo.tm_min = 30;

    time = getTime(&timeInfo);
   // date = getDate();

    REQUIRE(time == 1230);
   // REQUIRE(date <= 99991231 && date >= 00000101);
}
