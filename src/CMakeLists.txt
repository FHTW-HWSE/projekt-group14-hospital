
#Bit lower for copatability
cmake_minimum_required(VERSION 3.0)

set (CMAKE_C_COMPILER "gcc")

project (hospital14)

set (INCLUDE 
"../include")

find_package(Catch2 REQUIRED)
include(CTest)
include(Catch)

#set TESTING to false for normal build, and true for testing build
set (TESTING FALSE)


#if statement to disable the add executable when testing
if (NOT TESTING)


#normal build
add_executable(hospital14 main.cpp dateFunctions.cpp CSV_read.cpp CSV_write.cpp otherfunctions.cpp printFunctions.cpp )


else() 


set(TEST_BINARY ${PROJECT_NAME})
#testing build
add_executable(hospital14 dateFunctions.cpp CSV_read.cpp CSV_write.cpp otherfunctions.cpp printFunctions.cpp 
../tests/wait_and_prio_list_tests #../tests/seatingMap_tests.cpp  ../tests/test_CSV_write.cpp  # ../tests/dateFunctions_tests.cpp ../tests/test_CSV_read.cpp ../tests/test_otherfunctions.cpp ../tests/test_

)
target_link_libraries(hospital14 Catch2::Catch2)
catch_discover_tests(${TEST_BINARY})

endif()


#add_executable(hospital14 main.cpp dateFunctions.cpp CSV_read.cpp CSV_write.cpp otherfunctions.cpp printFunctions.cpp )






