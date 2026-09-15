#include <iostream>

#include "Zombie.hpp"

int main() {
  const int kHordeSize = 5;
  std::cout << "[N = " << kHordeSize << "] expect " << kHordeSize
            << " announces, then as many destructor messages\n";
  Zombie* horde = zombieHorde(kHordeSize, "Horde");
  for (int i = 0; i < kHordeSize; i++) {
    horde[i].announce();
  }
  delete[] horde;

  const int kEmptySize = 0;
  std::cout << "[N = " << kEmptySize << "] expect NULL, nothing allocated\n";
  Zombie* empty = zombieHorde(kEmptySize, "Empty");
  if (empty == NULL) {
    std::cout << "got NULL\n";
  }

  return 0;
}
