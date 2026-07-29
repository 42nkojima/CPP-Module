#include "Zombie.hpp"

int main() {
  Zombie* z = newZombie("Heap");
  z->announce();

  randomChump("Stack");
  delete z;

  return 0;
}
