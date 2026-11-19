#include <iostream>

#include "ScalarConverter.hpp"

int main(int ac, char** av) {
  if (ac != 2) {
    std::cerr << "usage: " << av[0] << " <literal>\n"
              << "  e.g: " << av[0] << " 42, " << av[0] << " 4.2f, " << av[0]
              << " nan\n";
    return 1;
  }

  ScalarConverter::convert(av[1]);
  return 0;
}
