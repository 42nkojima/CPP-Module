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

 private:
  // raw_ holds the real value scaled by 2^kFractionalBits.
  // e.g. 42.42f -> 10860, so one unit of raw_ represents 1/256.
  static const int kFractionalBits = 8;
  int raw_;
};

std::ostream& operator<<(std::ostream& out, const Fixed& right);

#endif
