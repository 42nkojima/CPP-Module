#include "ScalarConverter.hpp"

#include <cctype>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "ScalarValues.hpp"

static std::string format(const ScalarValues& values) {
  std::ostringstream oss;

  oss << "char: ";
  if (!values.hasChar()) {
    oss << "impossible";
  } else if (!std::isprint(static_cast<unsigned char>(values.getChar()))) {
    oss << "Non displayable";
  } else {
    oss << "'" << values.getChar() << "'";
  }
  oss << "\n";

  oss << "int: ";
  if (!values.hasInt()) {
    oss << "impossible";
  } else {
    oss << values.getInt();
  }
  oss << "\n";

  oss << std::fixed << std::setprecision(1);

  oss << "float: ";
  if (!values.hasFloat()) {
    oss << "impossible";
  } else {
    oss << values.getFloat() << "f";
  }
  oss << "\n";

  oss << "double: ";
  if (!values.hasDouble()) {
    oss << "impossible";
  } else {
    oss << values.getDouble();
  }
  oss << "\n";

  return oss.str();
}

void ScalarConverter::convert(const std::string& literal) {
  (void)literal;

  ScalarValues values;
  values.setChar('*');
  values.setInt(42);
  values.setFloat(42.0f);
  values.setDouble(42.0);
  std::cout << format(values);
}

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter&) {}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter&) {
  return *this;
}

ScalarConverter::~ScalarConverter() {}
