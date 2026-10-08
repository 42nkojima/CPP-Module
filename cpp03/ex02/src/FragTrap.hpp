#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP

#include <string>

#include "ClapTrap.hpp"

class FragTrap : public ClapTrap {
 public:
  FragTrap();
  FragTrap(const FragTrap& copy);
  explicit FragTrap(const std::string& name);

  ~FragTrap();

  FragTrap& operator=(const FragTrap& copy);

  void highFivesGuys();
};

#endif
