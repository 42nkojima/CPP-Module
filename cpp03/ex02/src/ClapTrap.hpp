#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <string>

class ClapTrap {
 public:
  ClapTrap();
  ClapTrap(const ClapTrap& copy);
  explicit ClapTrap(const std::string& name);

  virtual ~ClapTrap();

  ClapTrap& operator=(const ClapTrap& copy);

  virtual void attack(const std::string& target);
  void takeDamage(unsigned int amount);
  void beRepaired(unsigned int amount);

 protected:
  std::string name_;
  unsigned int hit_pts_;
  unsigned int energy_pts_;
  unsigned int attack_dmg_;
};

#endif
