#include "ClapTrap.hpp"

#include <iostream>

ClapTrap::ClapTrap()
    : name_("default"), hit_pts_(10), energy_pts_(10), attack_dmg_(0) {
  std::cout << "Default constructor called\n";
}

ClapTrap::ClapTrap(const ClapTrap& copy) {
  std::cout << "Copy constructor called\n";
  *this = copy;
}

ClapTrap::ClapTrap(const std::string& name)
    : name_(name), hit_pts_(10), energy_pts_(10), attack_dmg_(0) {
  std::cout << "Constructor for the name " << name_ << " called\n";
}

ClapTrap::~ClapTrap() { std::cout << "Destructor called\n"; }

ClapTrap& ClapTrap::operator=(const ClapTrap& copy) {
  std::cout << "Copy assignment operator called\n";
  name_ = copy.name_;
  hit_pts_ = copy.hit_pts_;
  energy_pts_ = copy.energy_pts_;
  attack_dmg_ = copy.attack_dmg_;
  return *this;
}

void ClapTrap::attack(const std::string& target) {}

void ClapTrap::takeDamage(unsigned int amount) {}

void beRepaired(unsigned int amount) {}
