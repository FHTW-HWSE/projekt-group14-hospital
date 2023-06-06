add_library(fizzbuzz src/fizzbuzz.cpp)
target_include_directories(fizzbuzz PUBLIC include)

add_executable(fizzbuzz_test 
test/main.cpp 
test/fizzbuzz_test.cpp 
)

target_link_libraries(fizzbuzz_test fizzbuzz)

catch_discover_tests(fizzbuzz_test)
