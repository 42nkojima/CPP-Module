#ifndef WRONGANIMAL_HPP
#define WRONGANIMAL_HPP

#include <string>

class WrongAnimal {
 public:
  WrongAnimal();
  WrongAnimal(const WrongAnimal& copy);

  virtual ~WrongAnimal();

  WrongAnimal& operator=(const WrongAnimal& copy);

  const std::string& getType() const;
  void makeSound() const;

 protected:
  std::string type;
};

#endif
