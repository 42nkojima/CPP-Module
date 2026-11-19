#include "Literal.hpp"

#include <cassert>

Literal::Literal() : type_(kInvalid) { value_.d = 0.0; }

Literal::Literal(const Literal& copy)
    : type_(copy.type_), value_(copy.value_) {}

Literal::Literal(char value) : type_(kChar) { value_.c = value; }

Literal::Literal(int value) : type_(kInt) { value_.i = value; }

Literal::Literal(float value) : type_(kFloat) { value_.f = value; }

Literal::Literal(double value) : type_(kDouble) { value_.d = value; }

Literal& Literal::operator=(const Literal& copy) {
  if (this != &copy) {
    type_ = copy.type_;
    value_ = copy.value_;
  }
  return *this;
}

Literal::~Literal() {}

Literal::Type Literal::getType() const { return type_; }

char Literal::getChar() const {
  assert(type_ == kChar);
  return value_.c;
}

int Literal::getInt() const {
  assert(type_ == kInt);
  return value_.i;
}

float Literal::getFloat() const {
  assert(type_ == kFloat);
  return value_.f;
}

double Literal::getDouble() const {
  assert(type_ == kDouble);
  return value_.d;
}
