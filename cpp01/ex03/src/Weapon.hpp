#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <string>

class Weapon {
 public:
  explicit Weapon(const std::string& type);
  ~Weapon();

  void setType(const std::string& type);
  const std::string& getType() const;

 private:
  std::string type_;
};

#endif
