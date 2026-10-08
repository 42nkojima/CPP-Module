#include <iostream>

#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

static void testSubject() {
  std::cout << std::endl << "--- subject ---" << std::endl;

  const Animal* meta = new Animal();
  const Animal* j = new Dog();
  const Animal* i = new Cat();

  std::cout << j->getType() << std::endl;
  std::cout << i->getType() << std::endl;
  i->makeSound();  // will output the cat sound!
  j->makeSound();
  meta->makeSound();

  delete meta;
  delete j;
  delete i;
}

static void testWrongAnimal() {
  std::cout << std::endl << "--- wrong animal ---" << std::endl;

  const WrongAnimal* meta = new WrongAnimal();
  const WrongAnimal* i = new WrongCat();

  std::cout << i->getType() << std::endl;
  i->makeSound();  // WrongAnimal's sound: makeSound is not virtual
  meta->makeSound();

  delete meta;
  delete i;
}

static void testDirectCall() {
  std::cout << std::endl << "--- direct call ---" << std::endl;

  WrongCat c;
  c.makeSound();  // WrongCat's sound: the static type is WrongCat
}

static void testReference() {
  std::cout << std::endl << "--- reference ---" << std::endl;

  Dog d;
  const Animal& ref = d;
  ref.makeSound();  // Dog's sound: virtual works through references too
}

static void testCopy() {
  std::cout << std::endl << "--- copy ---" << std::endl;

  Dog a;
  Dog b(a);  // Animal copy -> Dog copy
  Dog c;
  c = a;  // Dog assignment -> Animal assignment
  std::cout << b.getType() << " " << c.getType() << std::endl;
}

int main() {
  testSubject();
  testWrongAnimal();
  testDirectCall();
  testReference();
  testCopy();
  return 0;
}
