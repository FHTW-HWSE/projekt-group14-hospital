
#Bit lower for copatability
cmake_minimum_required(VERSION 3.0)

set (CMAKE_C_COMPILER "gcc")

project (hospital14)

set (INCLUDE 
"../include")

add_executable ( hospital14
main.cpp
dateFunctions.cpp
CSV_read.cpp
CSV_write.cpp
)


find_package(Catch2 REQUIRED)

include(CTest)

include(Catch)




