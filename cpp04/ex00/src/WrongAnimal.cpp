#include "WrongAnimal.hpp"

#include <iostream>

WrongAnimal::WrongAnimal() : type("WrongAnimal") {
  std::cout << "WrongAnimal default constructor called\n";
}

WrongAnimal::WrongAnimal(const WrongAnimal& copy) : type(copy.type) {
  std::cout << "WrongAnimal copy constructor called\n";
}

WrongAnimal::~WrongAnimal() { std::cout << "WrongAnimal destructor called\n"; }

WrongAnimal& WrongAnimal::operator=(const WrongAnimal& copy) {
  std::cout << "WrongAnimal copy assignment operator called\n";
  if (this != &copy) {
    type = copy.type;
  }
  return *this;
}

const std::string& WrongAnimal::getType() const { return type; }

void WrongAnimal::makeSound() const { std::cout << "* wrong animal sound *\n"; }
