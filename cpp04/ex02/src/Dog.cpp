#include "Dog.hpp"

#include <iostream>

Dog::Dog() : Animal(), brain_(new Brain()) {
  type = "Dog";
  std::cout << "Dog default constructor called\n";
}

Dog::Dog(const Dog& copy) : Animal(copy), brain_(new Brain(*copy.brain_)) {
  std::cout << "Dog copy constructor called\n";
}

Dog::~Dog() {
  std::cout << "Dog destructor called\n";
  delete brain_;
}

Dog& Dog::operator=(const Dog& copy) {
  std::cout << "Dog copy assignment operator called\n";
  if (this != &copy) {
    Animal::operator=(copy);
    *brain_ = *copy.brain_;
  }
  return *this;
}

void Dog::makeSound() const { std::cout << "Woof!\n"; }

std::string Dog::getIdea(int index) const { return brain_->getIdea(index); }

void Dog::setIdea(int index, const std::string& idea) {
  brain_->setIdea(index, idea);
}
