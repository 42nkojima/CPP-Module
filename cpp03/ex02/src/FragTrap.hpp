#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP

#include <string>

#include "ClapTrap.hpp"

class FragTrap : public ClapTrap {
 public:
  FragTrap();
  FragTrap(const FragTrap& copy);
  explicit FragTrap(const std::string& name);

  FragTrap& operator=(const FragTrap& copy);

  virtual ~FragTrap();

  void highFivesGuys();
};

#endif
