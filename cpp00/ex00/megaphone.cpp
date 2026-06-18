#include <cctype>
#include <iostream>

static void to_uppercase(std::string &str) {
  for (size_t i = 0; i < str.length(); i++) {
    str[i] = std::toupper(static_cast<unsigned char>(str[i]));
  }
}

int main(int ac, char **av) {
  if (ac == 1) {
    std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
    return 0;
  }

  for (int i = 1; i < ac; i++) {
    std::string str = av[i];
    to_uppercase(str);
    std::cout << str;
  }
  std::cout << std::endl;

  return 0;
}