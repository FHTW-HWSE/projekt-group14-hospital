
#Bit lower for copatability
cmake_minimum_required(VERSION 3.0)

set (CMAKE_C_COMPILER "gcc")

project (hospital14)

set (INCLUDE 
"../include")

find_package(Catch2 REQUIRED)
include(CTest)
include(Catch)
############################################    CMAKE FLAGS    ############################################
#set TESTING to false for normal build, and true for testing build
set (TESTING FALSE)
set (TESTEVERYTHING FALSE)

#select which Testfile will be compiled
#!!only select one at a time!! <or compiling will be no bueno>
set(T_date_functions FALSE)
set(T_file_handling FALSE)
set(T_seatingMap FALSE)
set(T_CSV_write FALSE)
set(T_CSV_read FALSE)
set(T_print_function_GernerateString FALSE)
set(T_wait_and_prio_list FALSE)
set(T_addNewPatients_tests FALSE)


#if statement to disable the add executable when testing
if (NOT TESTING)
#normal build

add_executable(hospital14 main.cpp dateFunctions.cpp CSV_read.cpp CSV_write.cpp otherfunctions.cpp printFunctions.cpp )


else if(TESTING TESTEVERYTHING)
add_executable(hospital14 dateFunctions.cpp CSV_read.cpp CSV_write.cpp otherfunctions.cpp printFunctions.cpp
../tests/main_test.include
../tests/dateFunctions_tests.cpp
../tests/file_handling.cpp
../tests/seatingMap_tests.cpp
../tests/test_CSV_write.cpp
../tests/test_PrintFunction_GenerateString.cpp
../tests/wait_and_prio_list_tests 
../tests/addNewPatients_tests.cpp
)    
endif(TESTING TESTEVERY)
()
#testing build

set(TEST_BINARY ${PROJECT_NAME})

#determine which testfile will be compiled
if(T_date_functions)
add_executable(hospital14 dateFunctions.cpp CSV_read.cpp CSV_write.cpp otherfunctions.cpp printFunctions.cpp 
../tests/dateFunctions_tests.cpp
)
endif()
if(T_file_handling)
add_executable(hospital14 dateFunctions.cpp CSV_read.cpp CSV_write.cpp otherfunctions.cpp printFunctions.cpp 
../tests/file_handling.cpp
)
endif()
if(T_seatingMap)
add_executable(hospital14 dateFunctions.cpp CSV_read.cpp CSV_write.cpp otherfunctions.cpp printFunctions.cpp 
../tests/seatingMap_tests.cpp
)
endif()

if(T_CSV_write)
add_executable(hospital14 dateFunctions.cpp CSV_read.cpp CSV_write.cpp otherfunctions.cpp printFunctions.cpp 
../tests/test_CSV_write.cpp
)
endif()

if(T_CSV_read)
add_executable(hospital14 dateFunctions.cpp CSV_read.cpp CSV_write.cpp otherfunctions.cpp printFunctions.cpp 
../tests/test_csv_read.cpp
)
endif()


if(T_print_function_GernerateString)
add_executable(hospital14 dateFunctions.cpp CSV_read.cpp CSV_write.cpp otherfunctions.cpp printFunctions.cpp 
../tests/test_PrintFunction_GenerateString.cpp
)
endif()
if(T_wait_and_prio_list)
add_executable(hospital14 dateFunctions.cpp CSV_read.cpp CSV_write.cpp otherfunctions.cpp printFunctions.cpp 
../tests/wait_and_prio_list_tests 
)
endif()
if(T_addNewPatients_tests)
add_executable(hospital14 dateFunctions.cpp CSV_read.cpp CSV_write.cpp otherfunctions.cpp printFunctions.cpp 
../tests/addNewPatients_tests.cpp
)
endif()



target_link_libraries(hospital14 Catch2::Catch2)
catch_discover_tests(${TEST_BINARY})
endif()#end of if statement for testing or normal build


#add_executable(hospital14 main.cpp dateFunctions.cpp CSV_read.cpp CSV_write.cpp otherfunctions.cpp printFunctions.cpp )






