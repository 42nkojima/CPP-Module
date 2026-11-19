#include "identify.hpp"

#include <cstdlib>
#include <exception>
#include <iostream>

#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base* generate(void) {
  switch (std::rand() % 3) {
    case 0:
      return new A();
    case 1:
      return new B();
    default:
      return new C();
  }
}

void identify(Base* p) {
  if (dynamic_cast<A*>(p) != NULL) {
    std::cout << "A\n";
  } else if (dynamic_cast<B*>(p) != NULL) {
    std::cout << "B\n";
  } else if (dynamic_cast<C*>(p) != NULL) {
    std::cout << "C\n";
  } else {
    std::cout << "Unknown\n";
  }
}

void identify(Base& p) {
  try {
    (void)dynamic_cast<A&>(p);
    std::cout << "A\n";
    return;
  } catch (const std::exception&) {
  }

  try {
    (void)dynamic_cast<B&>(p);
    std::cout << "B\n";
    return;
  } catch (const std::exception&) {
  }

  try {
    (void)dynamic_cast<C&>(p);
    std::cout << "C\n";
    return;
  } catch (const std::exception&) {
  }

  std::cout << "Unknown\n";
}
