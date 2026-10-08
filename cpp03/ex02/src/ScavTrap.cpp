#include "ScavTrap.hpp"

#include <iostream>

ScavTrap::ScavTrap() : ClapTrap() {
  hit_pts_ = 100;
  energy_pts_ = 50;
  attack_dmg_ = 20;
  std::cout << "ScavTrap default constructor called\n";
}

ScavTrap::ScavTrap(const ScavTrap& copy) : ClapTrap(copy) {
  std::cout << "ScavTrap copy constructor called\n";
}

ScavTrap::ScavTrap(const std::string& name) : ClapTrap(name) {
  hit_pts_ = 100;
  energy_pts_ = 50;
  attack_dmg_ = 20;
  std::cout << "ScavTrap " << name_ << " constructor called\n";
}

ScavTrap::~ScavTrap() {
  std::cout << "ScavTrap " << name_ << " destructor called\n";
}

ScavTrap& ScavTrap::operator=(const ScavTrap& copy) {
  std::cout << "ScavTrap copy assignment operator called\n";
  ClapTrap::operator=(copy);
  return *this;
}

void ScavTrap::attack(const std::string& target) {
  if (hit_pts_ == 0 || energy_pts_ == 0) {
    std::cout << "ScavTrap " << name_ << " can't attack\n";
    return;
  }
  --energy_pts_;
  std::cout << "ScavTrap " << name_ << " fiercely attacks " << target
            << ", causing " << attack_dmg_ << " points of damage!\n";
}

void ScavTrap::guardGate() {
  std::cout << "ScavTrap " << name_ << " is now in Gate keeper mode\n";
}
