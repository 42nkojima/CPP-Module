#ifndef FIXED_HPP
#define FIXED_HPP

#include <ostream>
class Fixed {
 public:
  Fixed();
  Fixed(const Fixed& copy);
  Fixed(const int nb_integer);
  Fixed(const float nb_float);

  Fixed& operator=(const Fixed& copy);

  ~Fixed();

  int getRawBits() const;
  void setRawBits(const int raw);

  float toFloat() const;
  int toInt() const;

  bool operator>(const Fixed& copy) const;
  bool operator<(const Fixed& copy) const;
  bool operator>=(const Fixed& copy) const;
  bool operator<=(const Fixed& copy) const;
  bool operator==(const Fixed& copy) const;
  bool operator!=(const Fixed& copy) const;

 private:
  static const int kFractionalBits = 8;
  int raw_;
};

std::ostream& operator<<(std::ostream& out, const Fixed& right);

#endif
