#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <string>

class Brain {
 public:
  Brain();
  Brain(const Brain& copy);

  Brain& operator=(const Brain& copy);

  ~Brain();

  std::string getIdea(int index) const;
  void setIdea(int index, const std::string& idea);

 private:
  static const int kNumIdeas = 100;
  std::string ideas_[kNumIdeas];
};

#endif
