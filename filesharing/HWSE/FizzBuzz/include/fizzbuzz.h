#pragma once

#include <string>

/// @brief Convert numbers to their fizzbuzz representation
/// @param number is the number to convert
/// @returns "Fizz" if the number is divisible by 3
///          "Buzz" if the number is divisible by 5
///          "FizzBuzz" if the number is divisible by both 3 and 5
///          string representation of the number otherwise  std::to_string(num)
std::string fizzbuzz(int number);

// - think about negative numbers
// - what happens with 0 ?
