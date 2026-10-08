#include "ClapTrap.hpp"

#include <iostream>

ClapTrap::ClapTrap()
    : name_("default"), hit_pts_(10), energy_pts_(10), attack_dmg_(0) {
  std::cout << "ClapTrap default constructor called\n";
}

ClapTrap::ClapTrap(const ClapTrap& copy)
    : name_(copy.name_),
      hit_pts_(copy.hit_pts_),
      energy_pts_(copy.energy_pts_),
      attack_dmg_(copy.attack_dmg_) {
  std::cout << "ClapTrap copy constructor called\n";
}

ClapTrap::ClapTrap(const std::string& name)
    : name_(name), hit_pts_(10), energy_pts_(10), attack_dmg_(0) {
  std::cout << "ClapTrap " << name_ << " constructor called\n";
}

ClapTrap::~ClapTrap() {
  std::cout << "ClapTrap " << name_ << " destructor called\n";
}

ClapTrap& ClapTrap::operator=(const ClapTrap& copy) {
  std::cout << "ClapTrap copy assignment operator called\n";
  if (this != &copy) {
    name_ = copy.name_;
    hit_pts_ = copy.hit_pts_;
    energy_pts_ = copy.energy_pts_;
    attack_dmg_ = copy.attack_dmg_;
  }
  return *this;
}

void ClapTrap::attack(const std::string& target) {
  if (hit_pts_ == 0 || energy_pts_ == 0) {
    std::cout << "ClapTrap " << name_ << " can't attack\n";
    return;
  }
  --energy_pts_;
  std::cout << "ClapTrap " << name_ << " attacks " << target << ", causing "
            << attack_dmg_ << " points of damage!\n";
}

void ClapTrap::takeDamage(unsigned int amount) {
  if (amount >= hit_pts_) {
    hit_pts_ = 0;
  } else {
    hit_pts_ -= amount;
  }
  std::cout << "ClapTrap " << name_ << " takes " << amount
            << " points of damage! (HP: " << hit_pts_ << ")\n";
}

void ClapTrap::beRepaired(unsigned int amount) {
  if (hit_pts_ == 0 || energy_pts_ == 0) {
    std::cout << "ClapTrap " << name_ << " can't be repaired\n";
    return;
  }
  --energy_pts_;
  hit_pts_ += amount;
  std::cout << "ClapTrap " << name_ << " repairs itself for " << amount
            << " hit points! (HP: " << hit_pts_ << ")\n";
}
