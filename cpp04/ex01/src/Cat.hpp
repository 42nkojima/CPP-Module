#ifndef CAT_HPP
#define CAT_HPP

#include <string>

#include "Animal.hpp"

class Brain;

class Cat : public Animal {
 public:
  Cat();
  Cat(const Cat& copy);

  ~Cat();

  Cat& operator=(const Cat& copy);

  void makeSound() const;
  std::string getIdea(int index) const;
  void setIdea(int index, const std::string& idea);

 private:
  Brain* brain_;
};

#endif
