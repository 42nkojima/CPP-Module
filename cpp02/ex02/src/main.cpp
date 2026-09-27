#include <iostream>

#include "Fixed.hpp"

static void testSubject() {
  std::cout << "--- subject ---" << std::endl;

  Fixed a;
  Fixed const b(Fixed(5.05f) * Fixed(2));

  std::cout << a << std::endl;    // 0
  std::cout << ++a << std::endl;  // 0.00390625
  std::cout << a << std::endl;    // 0.00390625
  std::cout << a++ << std::endl;  // 0.00390625
  std::cout << a << std::endl;    // 0.0078125

  std::cout << b << std::endl;  // 10.1016

  std::cout << Fixed::max(a, b) << std::endl;  // 10.1016
}

static void testComparison() {
  std::cout << "--- comparison ---" << std::endl;

  Fixed const a(1.5f);
  Fixed const b(2);

  std::cout << (a > b) << std::endl;   // 0
  std::cout << (a < b) << std::endl;   // 1
  std::cout << (a >= a) << std::endl;  // 1
  std::cout << (a <= a) << std::endl;  // 1
  std::cout << (a == a) << std::endl;  // 1
  std::cout << (a != b) << std::endl;  // 1
}

static void testArithmetic() {
  std::cout << "--- arithmetic ---" << std::endl;

  Fixed const a(10.5f);
  Fixed const b(2);

  std::cout << (a + b) << std::endl;  // 12.5
  std::cout << (a - b) << std::endl;  // 8.5
  std::cout << (a * b) << std::endl;  // 21
  std::cout << (a / b) << std::endl;  // 5.25

  std::cout << (a / 0) << std::endl;  // error
}

static void testIncrementDecrement() {
  std::cout << "--- increment / decrement ---" << std::endl;

  Fixed a;

  std::cout << ++a << std::endl;  // 0.00390625
  std::cout << a++ << std::endl;  // 0.00390625
  std::cout << a << std::endl;    // 0.0078125
  std::cout << --a << std::endl;  // 0.00390625
  std::cout << a-- << std::endl;  // 0.00390625
  std::cout << a << std::endl;    // 0
}

static void testMinMax() {
  std::cout << "--- min / max ---" << std::endl;

  Fixed a(1.5f);
  Fixed b(2);
  Fixed const c(1.5f);
  Fixed const d(2);

  std::cout << Fixed::min(a, b) << std::endl;  // 1.5
  std::cout << Fixed::max(a, b) << std::endl;  // 2
  std::cout << Fixed::min(c, d) << std::endl;  // 1.5
  std::cout << Fixed::max(c, d) << std::endl;  // 2
}

int main(void) {
  testSubject();
  testComparison();
  testArithmetic();
  testIncrementDecrement();
  testMinMax();

  return 0;
}
