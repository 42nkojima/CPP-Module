#include <iostream>
#include <string>

int main() {
  std::string brain = "HI THIS IS BRAIN";
  std::string* stringPTR = &brain;
  std::string& stringREF = brain;

  // address
  std::cout << &brain << "\n";
  std::cout << stringPTR << "\n";
  std::cout << &stringREF << "\n";

  // value
  std::cout << brain << "\n";
  std::cout << *stringPTR << "\n";
  std::cout << stringREF << "\n";
  return 0;
}
