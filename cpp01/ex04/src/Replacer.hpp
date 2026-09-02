#ifndef REPLACER_HPP
#define REPLACER_HPP

#include <string>

class Replacer {
 public:
  Replacer(const std::string& from, const std::string& to);

  std::string Apply(const std::string& content) const;

 private:
  std::string from_;
  std::string to_;
};

#endif
