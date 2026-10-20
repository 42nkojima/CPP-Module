#include "Cat.hpp"

#include <iostream>

#include "Brain.hpp"

Cat::Cat() : Animal("Cat"), brain_(new Brain()) {
  std::cout << "Cat default constructor called\n";
}

Cat::Cat(const Cat& copy) : Animal(copy), brain_(new Brain(*copy.brain_)) {
  std::cout << "Cat copy constructor called\n";
}

Cat::~Cat() {
  std::cout << "Cat destructor called\n";
  delete brain_;
}

Cat& Cat::operator=(const Cat& copy) {
  std::cout << "Cat copy assignment operator called\n";
  if (this != &copy) {
    Animal::operator=(copy);
    *brain_ = *copy.brain_;
  }
  return *this;
}

void Cat::makeSound() const { std::cout << "Meow!\n"; }

std::string Cat::getIdea(int index) const { return brain_->getIdea(index); }

void Cat::setIdea(int index, const std::string& idea) {
  brain_->setIdea(index, idea);
}
