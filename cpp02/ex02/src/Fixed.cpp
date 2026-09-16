#include "Fixed.hpp"

#include <cmath>
#include <iostream>

Fixed::Fixed() : value_(0) { std::cout << "Default constructor called\n"; }

Fixed::Fixed(const Fixed& copy) {
  std::cout << "Copy constructor called\n";
  *this = copy;
}

Fixed::Fixed(const int nb_integer) : value_(nb_integer << kFractionalBits) {
  std::cout << "Int constructor called\n";
}

Fixed::Fixed(const float nb_float)
    : value_(static_cast<int>(roundf(nb_float * (1 << kFractionalBits)))) {
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

int Fixed::getRawBits() const { return value_; }

void Fixed::setRawBits(const int raw) { value_ = raw; }

float Fixed::toFloat() const {
  return static_cast<float>(value_) / (1 << kFractionalBits);
}

int Fixed::toInt() const { return value_ >> kFractionalBits; }

std::ostream& operator<<(std::ostream& out, const Fixed& right) {
  out << right.toFloat();
  return out;
}
