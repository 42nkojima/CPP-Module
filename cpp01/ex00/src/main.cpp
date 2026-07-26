#include "Zombie.hpp"

int main(void) {
  Zombie* z = newZombie("Heap");
  z->announce();

  randomChump("Stack");
  delete z;

  return 0;
}
