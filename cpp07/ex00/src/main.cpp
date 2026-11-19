#include <iostream>
#include <string>

#include "whatever.hpp"

static void testSubject() {
  std::cout << "--- subject ---\n";

  int a = 2;
  int b = 3;

  ::swap(a, b);
  std::cout << "a = " << a << ", b = " << b << std::endl;
  std::cout << "min( a, b ) = " << ::min(a, b) << std::endl;
  std::cout << "max( a, b ) = " << ::max(a, b) << std::endl;

  std::string c = "chaine1";
  std::string d = "chaine2";

  ::swap(c, d);
  std::cout << "c = " << c << ", d = " << d << std::endl;
  std::cout << "min( c, d ) = " << ::min(c, d) << std::endl;
  std::cout << "max( c, d ) = " << ::max(c, d) << std::endl;
}

static void testOtherTypes() {
  std::cout << "--- other types ---\n";

  double x = 4.2;
  double y = -4.2;

  ::swap(x, y);
  std::cout << "x = " << x << ", y = " << y << "\n";
  std::cout << "min( x, y ) = " << ::min(x, y) << "\n";
  std::cout << "max( x, y ) = " << ::max(x, y) << "\n";

  const char p = 'a';
  const char q = 'z';

  std::cout << "min( p, q ) = " << ::min(p, q) << "\n";
  std::cout << "max( p, q ) = " << ::max(p, q) << "\n";
}

static void testEqual() {
  std::cout << "--- equal values return the second ---\n";

  int a = 42;
  int b = 42;

  std::cout << "min: " << (&::min(a, b) == &b ? "second" : "first") << "\n";
  std::cout << "max: " << (&::max(a, b) == &b ? "second" : "first") << "\n";
}

int main() {
  testSubject();
  testOtherTypes();
  testEqual();
  return 0;
}
