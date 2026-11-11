#ifndef DOG_HPP
#define DOG_HPP

#include <string>

#include "Animal.hpp"

class Brain;

class Dog : public Animal {
 public:
  Dog();
  Dog(const Dog& copy);

  Dog& operator=(const Dog& copy);

  ~Dog();

  void makeSound() const;
  std::string getIdea(int index) const;
  void setIdea(int index, const std::string& idea);

 private:
  Brain* brain_;
};

#endif
