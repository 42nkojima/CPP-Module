#include "Dog.hpp"

#include <iostream>

Dog::Dog() : Animal() {
  type = "Dog";
  std::cout << "Dog default constructor called\n";
}

Dog::Dog(const Dog& copy) : Animal(copy) {
  std::cout << "Dog copy constructor called\n";
}

Dog::~Dog() { std::cout << "Dog destructor called\n"; }

Dog& Dog::operator=(const Dog& copy) {
  std::cout << "Dog copy assignment operator called\n";
  Animal::operator=(copy);
  return *this;
}

void Dog::makeSound() const { std::cout << "Woof!\n"; }
