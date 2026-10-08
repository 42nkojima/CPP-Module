#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <string>

class Animal {
 public:
  Animal();
  Animal(const Animal& copy);

  virtual ~Animal();

  Animal& operator=(const Animal& copy);

  const std::string& getType() const;
  virtual void makeSound() const;

 protected:
  std::string type;
};

#endif
