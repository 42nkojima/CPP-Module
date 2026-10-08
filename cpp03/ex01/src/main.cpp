#include <iostream>

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

static void testChaining() {
  std::cout << "--- chaining ---" << std::endl;

  ScavTrap s("Serena");  // ClapTrap -> ScavTrap
}  // ~ScavTrap -> ~ClapTrap

static void testScavTrap() {
  std::cout << "--- scavtrap ---" << std::endl;

  ScavTrap s("Serena");
  s.attack("Bob");   // ScavTrap's own message, 20 damage
  s.takeDamage(30);  // HP: 70
  s.beRepaired(10);  // HP: 80
  s.guardGate();
}

static void testNoHitPoints() {
  std::cout << "--- no hit points ---" << std::endl;

  ScavTrap s("Serena");
  s.takeDamage(1000);  // HP: 0
  s.attack("Bob");     // can't attack
  s.beRepaired(5);     // can't be repaired
}

static void testCopy() {
  std::cout << "--- copy ---" << std::endl;

  ScavTrap a("Serena");
  a.takeDamage(40);  // HP: 60

  ScavTrap b(a);     // ClapTrap copy -> ScavTrap copy
  b.takeDamage(10);  // HP: 50 (a is unaffected)

  ScavTrap c;
  c = a;
  c.takeDamage(0);  // HP: 60
}

static void testPolymorphism() {
  std::cout << "--- polymorphism ---" << std::endl;

  ClapTrap* p = new ScavTrap("Serena");
  p->attack("Bob");  // ScavTrap::attack (virtual)
  delete p;          // ~ScavTrap -> ~ClapTrap (virtual destructor)
}

int main() {
  testChaining();
  testScavTrap();
  testNoHitPoints();
  testCopy();
  testPolymorphism();
  return 0;
}
