#include "Cat.hpp"

#include <iostream>

Cat::Cat() : Animal() {
  type = "Cat";
  std::cout << "Cat default constructor called\n";
}

Cat::Cat(const Cat& copy) : Animal(copy) {
  std::cout << "Cat copy constructor called\n";
}

Cat::~Cat() { std::cout << "Cat destructor called\n"; }

Cat& Cat::operator=(const Cat& copy) {
  std::cout << "Cat copy assignment operator called\n";
  Animal::operator=(copy);
  return *this;
}

void Cat::makeSound() const { std::cout << "Meow!\n"; }
