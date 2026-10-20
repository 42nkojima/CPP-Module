#include "Animal.hpp"

#include <iostream>

Animal::Animal() : type("Animal") {
  std::cout << "Animal default constructor called\n";
}

Animal::Animal(const std::string& type) : type(type) {
  std::cout << "Animal type constructor called\n";
}

Animal::Animal(const Animal& copy) : type(copy.type) {
  std::cout << "Animal copy constructor called\n";
}

Animal::~Animal() {
  std::cout << "Animal destructor called (" << type << ")\n";
}

Animal& Animal::operator=(const Animal& copy) {
  std::cout << "Animal copy assignment operator called\n";
  if (this != &copy) {
    type = copy.type;
  }
  return *this;
}

const std::string& Animal::getType() const { return type; }
