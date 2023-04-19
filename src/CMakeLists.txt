
#Bit lower for copatability
cmake_minimum_required(VERSION 3.0)

set (CMAKE_C_COMPILER "gcc")

project (hospital14)

set (INCLUDE 
"../include")



add_executable (
hospital14
main.cpp
dateFunctions.cpp
CSV_read.cpp
CSV_write.cpp
)


find_package(Catch2 REQUIRED)

target_link_libraries(hospital14 Catch2::Catch2)



include(CTest)

include(Catch)




