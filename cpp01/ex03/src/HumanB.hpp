#ifndef HUMANB_HPP
#define HUMANB_HPP

#include <string>

#include "Weapon.hpp"

class HumanB {
 public:
  explicit HumanB(const std::string& name);
  ~HumanB();

  void setWeapon(const Weapon& weapon);
  void attack() const;

 private:
  const std::string name_;
  const Weapon* weapon_;
};

#endif
