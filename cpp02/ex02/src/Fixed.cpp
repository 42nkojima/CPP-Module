#include "Fixed.hpp"

#include <cmath>
#include <iostream>

Fixed::Fixed() : raw_(0) { std::cout << "Default constructor called\n"; }

Fixed::Fixed(const Fixed& copy) {
  std::cout << "Copy constructor called\n";
  *this = copy;
}

Fixed::Fixed(const int nb_integer) : raw_(nb_integer << kFractionalBits) {
  std::cout << "Int constructor called\n";
}

Fixed::Fixed(const float nb_float)
    : raw_(static_cast<int>(roundf(nb_float * (1 << kFractionalBits)))) {
  std::cout << "Float constructor called\n";
}

Fixed& Fixed::operator=(const Fixed& copy) {
  std::cout << "Copy assignment operator called\n";

  if (this != &copy) {
    setRawBits(copy.getRawBits());
  }
  return *this;
}

Fixed::~Fixed() { std::cout << "Destructor called\n"; }

int Fixed::getRawBits() const { return raw_; }

void Fixed::setRawBits(const int raw) { raw_ = raw; }

float Fixed::toFloat() const {
  return static_cast<float>(raw_) / (1 << kFractionalBits);
}

int Fixed::toInt() const { return raw_ / (1 << kFractionalBits); }

bool Fixed::operator>(const Fixed& rhs) const { return raw_ > rhs.raw_; }

bool Fixed::operator<(const Fixed& rhs) const { return raw_ < rhs.raw_; }

bool Fixed::operator>=(const Fixed& rhs) const { return raw_ >= rhs.raw_; }

bool Fixed::operator<=(const Fixed& rhs) const { return raw_ <= rhs.raw_; }

bool Fixed::operator==(const Fixed& rhs) const { return raw_ == rhs.raw_; }

bool Fixed::operator!=(const Fixed& rhs) const { return raw_ != rhs.raw_; }

Fixed Fixed::operator+(const Fixed& rhs) const {
  Fixed r;
  r.setRawBits(raw_ + rhs.raw_);
  return r;
}

Fixed Fixed::operator-(const Fixed& rhs) const {
  Fixed r;
  r.setRawBits(raw_ - rhs.raw_);
  return r;
}

Fixed Fixed::operator*(const Fixed& rhs) const {
  Fixed r;
  r.setRawBits((int)((long)raw_ * rhs.raw_) >> kFractionalBits);
  return r;
}

Fixed Fixed::operator/(const Fixed& rhs) const {
  Fixed r;
  r.setRawBits((int)((long)raw_ << kFractionalBits) / rhs.raw_);
  return r;
}

std::ostream& operator<<(std::ostream& out, const Fixed& right) {
  out << right.toFloat();
  return out;
}
