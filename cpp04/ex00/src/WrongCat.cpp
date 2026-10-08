#include "WrongCat.hpp"

#include <iostream>

WrongCat::WrongCat() : WrongAnimal() {
  type = "WrongCat";
  std::cout << "WrongCat default constructor called\n";
}

WrongCat::WrongCat(const WrongCat& copy) : WrongAnimal(copy) {
  std::cout << "WrongCat copy constructor called\n";
}

WrongCat::~WrongCat() { std::cout << "WrongCat destructor called\n"; }

WrongCat& WrongCat::operator=(const WrongCat& copy) {
  std::cout << "WrongCat copy assignment operator called\n";
  WrongAnimal::operator=(copy);
  return *this;
}

// cppcheck-suppress duplInheritedMember
void WrongCat::makeSound() const { std::cout << "Meow!\n"; }
