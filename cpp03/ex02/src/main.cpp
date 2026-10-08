#include <iostream>

#include "ClapTrap.hpp"
#include "FragTrap.hpp"
#include "ScavTrap.hpp"

static void testChaining() {
  std::cout << "--- chaining ---" << std::endl;

  ScavTrap s("Serena");   // ClapTrap -> ScavTrap
  FragTrap f("Frankie");  // ClapTrap -> FragTrap
}  // ~FragTrap -> ~ClapTrap -> ~ScavTrap -> ~ClapTrap

static void testScavTrap() {
  std::cout << "--- scavtrap ---" << std::endl;

  ScavTrap s("Serena");
  s.attack("Bob");   // ScavTrap's own message, 20 damage
  s.takeDamage(30);  // HP: 70
  s.beRepaired(10);  // HP: 80
  s.guardGate();
}

static void testFragTrap() {
  std::cout << "--- fragtrap ---" << std::endl;

  FragTrap f("Frankie");
  f.attack("Bob");   // ClapTrap's message, 30 damage
  f.takeDamage(30);  // HP: 70
  f.beRepaired(10);  // HP: 80
  f.highFivesGuys();
}

static void testNoHitPoints() {
  std::cout << "--- no hit points ---" << std::endl;

  FragTrap f("Frankie");
  f.takeDamage(1000);  // HP: 0
  f.attack("Bob");     // can't attack
  f.beRepaired(5);     // can't be repaired
}

static void testCopy() {
  std::cout << "--- copy ---" << std::endl;

  FragTrap a("Frankie");
  a.takeDamage(40);  // HP: 60

  FragTrap b(a);     // ClapTrap copy -> FragTrap copy
  b.takeDamage(10);  // HP: 50 (a is unaffected)

  FragTrap c;
  c = a;
  c.takeDamage(0);  // HP: 60
}

static void testPolymorphism() {
  std::cout << "--- polymorphism ---" << std::endl;

  ClapTrap* robots[2] = {new ScavTrap("Serena"), new FragTrap("Frankie")};
  for (int i = 0; i < 2; ++i) {
    robots[i]->attack("Bob");  // ScavTrap::attack, ClapTrap::attack
  }
  for (int i = 0; i < 2; ++i) {
    delete robots[i];  // ~ScavTrap/~FragTrap -> ~ClapTrap
  }
}

int main() {
  testChaining();
  testScavTrap();
  testFragTrap();
  testNoHitPoints();
  testCopy();
  testPolymorphism();
  return 0;
}
