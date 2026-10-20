#include <iostream>
#include <string>

#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

static void printIdea(const std::string& name, const std::string& idea) {
  std::cout << name << ": \"" << idea << "\"" << std::endl;
}

static void testSubject() {
  std::cout << std::endl << "--- subject ---" << std::endl;

  const Animal* j = new Dog();
  const Animal* i = new Cat();

  delete j;  // should not create a leak
  delete i;
}

static void testArray() {
  std::cout << std::endl << "--- array ---" << std::endl;

  const int kNumAnimals = 4;
  Animal* animals[kNumAnimals];
  for (int i = 0; i < kNumAnimals; ++i) {
    if (i < kNumAnimals / 2) {
      animals[i] = new Dog();
    } else {
      animals[i] = new Cat();
    }
  }
  for (int i = 0; i < kNumAnimals; ++i) {
    animals[i]->makeSound();
  }
  for (int i = 0; i < kNumAnimals; ++i) {
    delete animals[i];
  }
}

static void testCopyConstructor() {
  std::cout << std::endl << "--- deep copy: copy constructor ---" << std::endl;

  Dog a;
  a.setIdea(0, "chase the ball");

  Dog b(a);
  b.setIdea(0, "dig a hole");

  printIdea("a", a.getIdea(0));
  printIdea("b", b.getIdea(0));
}

static void testCopyAssignment() {
  std::cout << std::endl << "--- deep copy: copy assignment ---" << std::endl;

  Cat a;
  a.setIdea(0, "sleep all day");

  Cat b;
  b = a;
  b.setIdea(0, "knock things over");

  printIdea("a", a.getIdea(0));
  printIdea("b", b.getIdea(0));
}

static void testAbstract() {
  std::cout << std::endl << "--- abstract ---" << std::endl;

  // const Animal* meta = new Animal(); // error: Animal is abstract
  // Dog d; Cat c; Animal& ref = d;
  // ref = c; // error: Animal::operator= is protected
  const Animal* dog = new Dog();
  dog->makeSound();
  delete dog;
}

int main() {
  testSubject();
  testArray();
  testCopyConstructor();
  testCopyAssignment();
  testAbstract();
  return 0;
}
