#include <cstddef>
#include <iostream>
#include <string>

#include "iter.hpp"

template <typename T>
static void print(const T& value) {
  std::cout << value << " ";
}

static void increment(int& value) { ++value; }

static void shout(std::string& value) { value += "!"; }

static void testInt() {
  std::cout << "--- int ---" << std::endl;

  int numbers[] = {1, 2, 3, 4, 5};
  const std::size_t length = sizeof(numbers) / sizeof(numbers[0]);

  ::iter(numbers, length, print<int>);
  std::cout << std::endl;

  ::iter(numbers, length, increment);
  ::iter(numbers, length, print<int>);
  std::cout << std::endl;
}

static void testConst() {
  std::cout << "--- const int ---" << std::endl;

  const int numbers[] = {10, 20, 30};

  ::iter(numbers, 3, print<int>);
  std::cout << std::endl;
}

static void testString() {
  std::cout << "--- std::string ---" << std::endl;

  std::string words[] = {"hello", "world"};

  ::iter(words, 2, print<std::string>);
  std::cout << std::endl;

  ::iter(words, 2, shout);
  ::iter(words, 2, print<std::string>);
  std::cout << std::endl;
}

static void testEmpty() {
  std::cout << "--- length 0 ---" << std::endl;

  int numbers[] = {1, 2, 3};

  ::iter(numbers, 0, print<int>);
  std::cout << std::endl;
}

int main() {
  testInt();
  testConst();
  testString();
  testEmpty();
  return 0;
}
