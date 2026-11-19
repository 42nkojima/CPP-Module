#include <cstdlib>
#include <ctime>
#include <iostream>

#include "A.hpp"
#include "B.hpp"
#include "Base.hpp"
#include "C.hpp"
#include "identify.hpp"

static void identifyBoth(Base* p) {
  std::cout << "pointer:   ";
  identify(p);
  std::cout << "reference: ";
  identify(*p);
}

static void testEachType() {
  std::cout << "--- each type ---\n";

  A a;
  B b;
  C c;

  identifyBoth(&a);
  identifyBoth(&b);
  identifyBoth(&c);
}

static void testGenerate() {
  std::cout << "--- generate ---\n";

  for (int i = 0; i < 6; ++i) {
    Base* p = generate();
    identifyBoth(p);
    delete p;
  }
}

static void testUnknown() {
  std::cout << "--- not A, B or C ---\n";

  Base base;
  identifyBoth(&base);

  std::cout << "null:      ";
  identify(static_cast<Base*>(NULL));
}

int main() {
  std::srand(std::time(NULL));

  testEachType();
  testGenerate();
  testUnknown();
  return 0;
}
