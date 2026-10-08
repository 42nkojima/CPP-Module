#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

#include <string>

#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap {
 public:
  ScavTrap();
  ScavTrap(const ScavTrap& copy);
  explicit ScavTrap(const std::string& name);

  ~ScavTrap();

  ScavTrap& operator=(const ScavTrap& copy);

  void attack(const std::string& target);
  void guardGate();
};

#endif
