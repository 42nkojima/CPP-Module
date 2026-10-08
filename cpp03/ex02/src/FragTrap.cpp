#include "FragTrap.hpp"

#include <iostream>

FragTrap::FragTrap() : ClapTrap() {
  hit_pts_ = 100;
  energy_pts_ = 100;
  attack_dmg_ = 30;
  std::cout << "FragTrap default constructor called\n";
}

FragTrap::FragTrap(const FragTrap& copy) : ClapTrap(copy) {
  std::cout << "FragTrap copy constructor called\n";
}

FragTrap::FragTrap(const std::string& name) : ClapTrap(name) {
  hit_pts_ = 100;
  energy_pts_ = 100;
  attack_dmg_ = 30;
  std::cout << "FragTrap " << name_ << " constructor called\n";
}

FragTrap::~FragTrap() {
  std::cout << "FragTrap " << name_ << " destructor called\n";
}

FragTrap& FragTrap::operator=(const FragTrap& copy) {
  std::cout << "FragTrap copy assignment operator called\n";
  ClapTrap::operator=(copy);
  return *this;
}

void FragTrap::highFivesGuys() {
  std::cout << "FragTrap " << name_ << " requests a high five!\n";
}
