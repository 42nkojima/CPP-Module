#include "FileReplacer.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

FileReplacer::FileReplacer(const std::string& filename,
                           const Replacer& replacer)
    : filename_(filename), replacer_(replacer) {}

bool FileReplacer::Execute() const {
  std::ifstream ifs(filename_.c_str());
  if (!ifs) {
    std::cerr << "cannot open " << filename_ << "\n";
    return false;
  }

  std::ostringstream oss;
  oss << ifs.rdbuf();
  std::string content = oss.str();

  std::string replaced = replacer_.Apply(content);

  std::string output_path = filename_ + ".replace";
  std::ofstream ofs(output_path.c_str());
  if (!ofs) {
    std::cerr << "cannot create " << output_path << "\n";
    return false;
  }

  ofs << replaced;
  ofs.flush();
  if (!ofs) {
    std::cerr << "cannot write to " << output_path << "\n";
    return false;
  }

  return true;
}
