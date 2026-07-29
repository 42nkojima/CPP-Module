#include <iostream>

#include "Zombie.hpp"

int main() {
  const int hordeSize = 5;
  std::cout << "[N = " << hordeSize << "] expect " << hordeSize
            << " announces, then as many destructor messages\n";
  Zombie* horde = zombieHorde(hordeSize, "Horde");
  for (int i = 0; i < hordeSize; i++) {
    horde[i].announce();
  }
  delete[] horde;

  const int emptySize = 0;
  std::cout << "[N = " << emptySize << "] expect NULL, nothing allocated\n";
  Zombie* empty = zombieHorde(emptySize, "Empty");
  if (empty == NULL) std::cout << "got NULL\n";

  return 0;
}
