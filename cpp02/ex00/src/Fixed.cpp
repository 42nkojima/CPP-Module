#include "Fixed.hpp"

#include <iostream>

Fixed::Fixed() : raw_(0) { std::cout << "Default constructor called\n"; }

Fixed::Fixed(const Fixed& copy) {
  std::cout << "Copy constructor called\n";
  *this = copy;
}

Fixed& Fixed::operator=(const Fixed& copy) {
  std::cout << "Copy assignment operator called\n";

  if (this != &copy) {
    setRawBits(copy.getRawBits());
  }
  return *this;
}

Fixed::~Fixed() { std::cout << "Destructor called\n"; }

int Fixed::getRawBits() const {
  std::cout << "getRawBits member function called\n";
  return raw_;
}

void Fixed::setRawBits(const int raw) { raw_ = raw; }
