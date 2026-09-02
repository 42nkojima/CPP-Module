#include "Replacer.hpp"

Replacer::Replacer(const std::string& from, const std::string& to)
    : from_(from), to_(to) {}

std::string Replacer::Apply(const std::string& content) const {
  if (from_.empty()) return content;

  std::string result;
  std::string::size_type start = 0, pos;
  while ((pos = content.find(from_, start)) != std::string::npos) {
    result += content.substr(start, pos - start) + to_;
    start = pos + from_.length();
  }
  result += content.substr(start);

  return result;
}
