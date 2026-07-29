#include "Zombie.hpp"

#include <iostream>
#include <string>

Zombie::Zombie() {}

Zombie::Zombie(const std::string& name) : name_(name) {}

Zombie::~Zombie() { std::cout << name_ << ": died...\n"; }

void Zombie::announce() const {
  std::cout << name_ << ": BraiiiiiiinnnzzzZ...\n";
}

void Zombie::set_name(const std::string& name) { name_ = name; }
