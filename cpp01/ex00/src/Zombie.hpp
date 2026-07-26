#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <string>

class Zombie {
 private:
  std::string name_;

 public:
  explicit Zombie(const std::string& name);
  ~Zombie(void);

  void announce(void) const;
};

Zombie* newZombie(const std::string& name);
void randomChump(const std::string& name);

#endif
