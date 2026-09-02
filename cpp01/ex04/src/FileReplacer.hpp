#ifndef FILEREPLACER_HPP
#define FILEREPLACER_HPP

#include <string>

#include "Replacer.hpp"

class FileReplacer {
 public:
  FileReplacer(const std::string& filename, const Replacer& replacer);
  bool Execute() const;

 private:
  std::string filename_;
  Replacer replacer_;
};

#endif
