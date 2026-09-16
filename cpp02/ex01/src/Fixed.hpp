#ifndef FIXED_HPP
#define FIXED_HPP

#include <ostream>

class Fixed {
 public:
  // constructors
  Fixed();
  Fixed(const Fixed& copy);
  Fixed(const int nb_integer);
  Fixed(const float nb_float);

  // assignment operators
  Fixed& operator=(const Fixed& copy);

  // destructor
  ~Fixed();

  // other functions
  int getRawBits() const;
  void setRawBits(const int raw);

  float toFloat() const;
  int toInt() const;

 private:
  // value_ holds the real value scaled by 2^kFractionalBits.
  // e.g. 42.42f -> 10860, so one unit of value_ represents 1/256.
  static const int kFractionalBits = 8;
  int value_;
};

std::ostream& operator<<(std::ostream& out, const Fixed& right);

#endif
