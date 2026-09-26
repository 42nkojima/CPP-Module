#include <iostream>

#include "Fixed.hpp"

static void testSubject() {
  std::cout << "--- subject ---" << std::endl;

  Fixed a;
  Fixed const b(Fixed(5.05f) * Fixed(2));

  std::cout << a << std::endl;
  std::cout << ++a << std::endl;
  std::cout << a << std::endl;
  std::cout << a++ << std::endl;
  std::cout << a << std::endl;

  std::cout << b << std::endl;

  std::cout << Fixed::max(a, b) << std::endl;
}

static void testComparison() {
  std::cout << "--- comparison ---" << std::endl;

  Fixed const a(1.5f);
  Fixed const b(2);

  std::cout << (a > b) << std::endl;
  std::cout << (a < b) << std::endl;
  std::cout << (a >= a) << std::endl;
  std::cout << (a <= a) << std::endl;
  std::cout << (a == a) << std::endl;
  std::cout << (a != b) << std::endl;
}

static void testArithmetic() {
  std::cout << "--- arithmetic ---" << std::endl;

  Fixed const a(10.5f);
  Fixed const b(2);

  std::cout << (a + b) << std::endl;
  std::cout << (a - b) << std::endl;
  std::cout << (a * b) << std::endl;
  std::cout << (a / b) << std::endl;
}

static void testIncrementDecrement() {
  std::cout << "--- increment / decrement ---" << std::endl;

  Fixed a;

  std::cout << ++a << std::endl;
  std::cout << a++ << std::endl;
  std::cout << a << std::endl;
  std::cout << --a << std::endl;
  std::cout << a-- << std::endl;
  std::cout << a << std::endl;
}

static void testMinMax() {
  std::cout << "--- min / max ---" << std::endl;

  Fixed a(1.5f);
  Fixed b(2);
  Fixed const c(1.5f);
  Fixed const d(2);

  std::cout << Fixed::min(a, b) << std::endl;
  std::cout << Fixed::max(a, b) << std::endl;
  std::cout << Fixed::min(c, d) << std::endl;
  std::cout << Fixed::max(c, d) << std::endl;
}

int main(void) {
  testSubject();
  testComparison();
  testArithmetic();
  testIncrementDecrement();
  testMinMax();

  return 0;
}
