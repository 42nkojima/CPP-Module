#include <string>

#include "Zombie.hpp"

Zombie* newZombie(const std::string& name) { return new Zombie(name); }
