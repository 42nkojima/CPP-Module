#include <iostream>
#include <string>

#include "FileReplacer.hpp"
#include "Replacer.hpp"

int main(int ac, char** av) {
  if (ac != 4) {
    std::cerr << "usage: " << av[0] << " <filename> <s1> <s2>\n";
    return 1;
  }

  std::string s1 = av[2];
  if (s1.empty()) {
    std::cerr << "<s1> must not be empty\n";
    return 1;
  }

  std::string s2 = av[3];
  Replacer replacer(s1, s2);
  FileReplacer file_replacer(av[1], replacer);

  return !file_replacer.Execute();
}
