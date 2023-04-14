
#Bit lower for copatability
cmake_minimum_required(VERSION 3.0)

set (CMAKE_C_COMPILER "gcc-4.2")

project (hospital14)

set (INCLUDE 
"../include")

add_executable(${<PROJECT-NAME>}
main.cpp
dateFunctions.cpp
file_handling.cpp

)


find_package(Catch2 REQIRED)

include(CTest)

include(Catch)
