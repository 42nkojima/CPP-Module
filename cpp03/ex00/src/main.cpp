#include <iostream>

#include "ClapTrap.hpp"

static void testBasic() {
  std::cout << "--- basic ---" << std::endl;

  ClapTrap a("Alice");
  a.attack("Bob");
  a.takeDamage(3);  // HP: 7
  a.beRepaired(2);  // HP: 9
}

static void testNoHitPoints() {
  std::cout << "--- no hit points ---" << std::endl;

  ClapTrap a("Alice");
  a.takeDamage(100);  // HP: 0 (no underflow)
  a.attack("Bob");    // can't attack
  a.beRepaired(5);    // can't be repaired
}

static void testNoEnergy() {
  std::cout << "--- no energy ---" << std::endl;

  ClapTrap a("Alice");
  for (int i = 0; i < 10; ++i) {
    a.attack("Bob");
  }
  a.attack("Bob");  // can't attack
  a.beRepaired(1);  // can't be repaired
}

static void testCopy() {
  std::cout << "--- copy ---" << std::endl;

  ClapTrap a("Alice");
  a.takeDamage(4);  // HP: 6

  ClapTrap b(a);
  b.takeDamage(1);  // HP: 5 (a is unaffected)

  ClapTrap c;
  c = a;
  c.takeDamage(0);  // HP: 6
}

int main() {
  testBasic();
  testNoHitPoints();
  testNoEnergy();
  testCopy();
  return 0;
}
