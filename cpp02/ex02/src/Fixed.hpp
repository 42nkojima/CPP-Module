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

  bool operator<(const Fixed& rhs) const;
  bool operator>(const Fixed& rhs) const;
  bool operator<=(const Fixed& rhs) const;
  bool operator>=(const Fixed& rhs) const;
  bool operator==(const Fixed& rhs) const;
  bool operator!=(const Fixed& rhs) const;

  Fixed operator+(const Fixed& rhs) const;
  Fixed operator-(const Fixed& rhs) const;
  Fixed operator*(const Fixed& rhs) const;
  Fixed operator/(const Fixed& rhs) const;

  Fixed& operator++();
  Fixed operator++(int);
  Fixed& operator--();
  Fixed operator--(int);

  static Fixed& min(Fixed& a, Fixed& b);
  static const Fixed& min(const Fixed& a, const Fixed& b);
  static Fixed& max(Fixed& a, Fixed& b);
  static const Fixed& max(const Fixed& a, const Fixed& b);

 private:
  static const int kFractionalBits = 8;
  int raw_;
};

std::ostream& operator<<(std::ostream& out, const Fixed& right);

#endif
