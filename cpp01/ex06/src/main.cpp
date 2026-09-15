#include <iostream>

#include "Harl.hpp"

int main(int ac, char** av) {
  if (ac != 2) {
    std::cerr << "usage: " << av[0] << " <DEBUG|INFO|WARNING|ERROR>\n";
    return 1;
  }

  Harl harl;
  harl.complainFilter(av[1]);

  return 0;
}
