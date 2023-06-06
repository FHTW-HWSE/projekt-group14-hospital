#include <fizzbuzz.h>

std::string fizzbuzz(int number) {
  // without the check 0 will be considered "FizzBuzz"
  // we could also support "-Fizz", "-Buzz", and "-FizzBuzz"
  if (number <= 0)
    return std::to_string(number);

  std::string result{};

  if (number % 3 == 0)
    result += "Fizz";

  if (number % 5 == 0)
    result += "Buzz";

  if (result.empty())
    return std::to_string(number);

  return result;
}
