#ifndef WRONGANIMAL_HPP
#define WRONGANIMAL_HPP

#include <string>

class WrongAnimal {
 public:
  WrongAnimal();
  WrongAnimal(const WrongAnimal& copy);

  WrongAnimal& operator=(const WrongAnimal& copy);

  virtual ~WrongAnimal();

  const std::string& getType() const;
  void makeSound() const;

 protected:
  explicit WrongAnimal(const std::string& type);

  std::string type;
};

#endif
