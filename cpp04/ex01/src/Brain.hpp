#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <string>

class Brain {
 public:
  Brain();
  Brain(const Brain& copy);

  ~Brain();

  Brain& operator=(const Brain& copy);

  std::string getIdea(int index) const;
  void setIdea(int index, const std::string& idea);

 private:
  static const int kNumIdeas = 100;
  std::string ideas[kNumIdeas];
};

#endif
