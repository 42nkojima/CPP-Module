#ifndef WRONGCAT_HPP
#define WRONGCAT_HPP

#include "WrongAnimal.hpp"

class WrongCat : public WrongAnimal {
 public:
  WrongCat();
  WrongCat(const WrongCat& copy);

  WrongCat& operator=(const WrongCat& copy);

  ~WrongCat();

  // Hiding the non-virtual WrongAnimal::makeSound is the point of WrongCat.
  // cppcheck-suppress duplInheritedMember
  void makeSound() const;
};

#endif
