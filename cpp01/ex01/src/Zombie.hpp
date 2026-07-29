#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <string>

class Zombie {
 public:
  Zombie();
  explicit Zombie(const std::string& name);
  ~Zombie();

  void announce() const;
  void set_name(const std::string& name);

 private:
  std::string name_;
};

Zombie* zombieHorde(int N, const std::string& name);

#endif
