#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <string>

class Animal {
 public:
  Animal();
  Animal(const Animal& copy);

  virtual ~Animal();

  const std::string& getType() const;
  virtual void makeSound() const = 0;

 protected:
  explicit Animal(const std::string& type);

  // Assigning through Animal& would copy only the Animal part (e.g. a Dog
  // ending up with type "Cat"), so only derived classes may call it.
  Animal& operator=(const Animal& copy);

  std::string type;
};

#endif
