#include "Zombie.hpp"

#include <iostream>
#include <string>

Zombie::Zombie(const std::string& name) : name_(name) {}

Zombie::~Zombie(void) { std::cout << name_ << ": died...\n"; }

void Zombie::announce(void) const {
  std::cout << name_ << ": BraiiiiiiinnnzzzZ...\n";
}
