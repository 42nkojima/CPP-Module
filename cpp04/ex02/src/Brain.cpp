#include "Brain.hpp"

#include <iostream>

Brain::Brain() { std::cout << "Brain default constructor called\n"; }

Brain::Brain(const Brain& copy) {
  std::cout << "Brain copy constructor called\n";
  for (int i = 0; i < kNumIdeas; i++) {
    ideas[i] = copy.ideas[i];
  }
}

Brain::~Brain() { std::cout << "Brain destructor called\n"; }

Brain& Brain::operator=(const Brain& copy) {
  std::cout << "Brain copy assignment operator called\n";
  if (this != &copy) {
    for (int i = 0; i < kNumIdeas; i++) {
      ideas[i] = copy.ideas[i];
    }
  }
  return *this;
}

std::string Brain::getIdea(int index) const {
  if (index < 0 || index >= kNumIdeas) {
    return "";
  }
  return ideas[index];
}

void Brain::setIdea(int index, const std::string& idea) {
  if (index < 0 || index >= kNumIdeas) {
    return;
  }
  ideas[index] = idea;
}
