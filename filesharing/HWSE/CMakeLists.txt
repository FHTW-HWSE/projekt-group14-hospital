cmake_minimum_required(VERSION 3.10.0)

project(HWSE VERSION 1.0)

find_package(Catch2 REQUIRED)

include(CTest)
include(Catch)

add_subdirectory(FizzBuzz)

