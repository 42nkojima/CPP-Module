#ifndef DOG_HPP
#define DOG_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal {
 public:
  Dog();
  Dog(const Dog& copy);

  ~Dog();

  Dog& operator=(const Dog& copy);

  void makeSound() const;
  Brain* getBrain() const;

 private:
  Brain* brain_;
};

#endif
