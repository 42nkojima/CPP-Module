#include "ScalarValues.hpp"

#include <cassert>

ScalarValues::ScalarValues()
    : has_char_(false),
      char_value_('\0'),

      has_int_(false),
      int_value_(0),

      has_float_(false),
      float_value_(0.0f),

      has_double_(false),
      double_value_(0.0) {}

ScalarValues::ScalarValues(const ScalarValues& copy)
    : has_char_(copy.has_char_),
      char_value_(copy.char_value_),

      has_int_(copy.has_int_),
      int_value_(copy.int_value_),

      has_float_(copy.has_float_),
      float_value_(copy.float_value_),

      has_double_(copy.has_double_),
      double_value_(copy.double_value_) {}

ScalarValues& ScalarValues::operator=(const ScalarValues& copy) {
  if (this != &copy) {
    has_char_ = copy.has_char_;
    char_value_ = copy.char_value_;

    has_int_ = copy.has_int_;
    int_value_ = copy.int_value_;

    has_float_ = copy.has_float_;
    float_value_ = copy.float_value_;

    has_double_ = copy.has_double_;
    double_value_ = copy.double_value_;
  }
  return *this;
}

ScalarValues::~ScalarValues() {}

bool ScalarValues::hasChar() const { return has_char_; }

char ScalarValues::getChar() const {
  assert(has_char_);
  return char_value_;
}

void ScalarValues::setChar(char value) {
  char_value_ = value;
  has_char_ = true;
}

bool ScalarValues::hasInt() const { return has_int_; }

int ScalarValues::getInt() const {
  assert(has_int_);
  return int_value_;
}

void ScalarValues::setInt(int value) {
  int_value_ = value;
  has_int_ = true;
}

bool ScalarValues::hasFloat() const { return has_float_; }

float ScalarValues::getFloat() const {
  assert(has_float_);
  return float_value_;
}

void ScalarValues::setFloat(float value) {
  float_value_ = value;
  has_float_ = true;
}

bool ScalarValues::hasDouble() const { return has_double_; }

double ScalarValues::getDouble() const {
  assert(has_double_);
  return double_value_;
}

void ScalarValues::setDouble(double value) {
  double_value_ = value;
  has_double_ = true;
}
