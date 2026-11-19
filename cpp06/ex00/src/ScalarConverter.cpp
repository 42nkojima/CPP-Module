#include "ScalarConverter.hpp"

#include <cctype>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

#include "Literal.hpp"
#include "ScalarValues.hpp"

static bool fitsInChar(double value) {
  return value >= std::numeric_limits<char>::min() &&
         value <= std::numeric_limits<char>::max();
}

static bool fitsInInt(double value) {
  return value >= std::numeric_limits<int>::min() &&
         value <= std::numeric_limits<int>::max();
}

static bool fitsInFloat(double value) {
  const double infinity = std::numeric_limits<double>::infinity();
  if (value != value || value == infinity || value == -infinity) {
    return true;
  }
  return value >= -std::numeric_limits<float>::max() &&
         value <= std::numeric_limits<float>::max();
}

static bool isIntegerForm(const std::string& str) {
  std::string::size_type i = (str[0] == '+' || str[0] == '-') ? 1 : 0;
  if (i == str.length()) {
    return false;
  }
  for (; i < str.length(); ++i) {
    if (!std::isdigit(static_cast<unsigned char>(str[i]))) {
      return false;
    }
  }
  return true;
}

static bool isDecimalForm(const std::string& str) {
  std::string::size_type i = (str[0] == '+' || str[0] == '-') ? 1 : 0;
  int digits = 0;
  int dots = 0;
  for (; i < str.length(); ++i) {
    if (str[i] == '.') {
      ++dots;
    } else if (std::isdigit(static_cast<unsigned char>(str[i]))) {
      ++digits;
    } else {
      return false;
    }
  }
  return dots == 1 && digits > 0;
}

static Literal parsePseudoLiteral(const std::string& str) {
  if (str == "nanf") {
    return Literal(std::numeric_limits<float>::quiet_NaN());
  }
  if (str == "+inff") {
    return Literal(std::numeric_limits<float>::infinity());
  }
  if (str == "-inff") {
    return Literal(-std::numeric_limits<float>::infinity());
  }
  if (str == "nan") {
    return Literal(std::numeric_limits<double>::quiet_NaN());
  }
  if (str == "+inf") {
    return Literal(std::numeric_limits<double>::infinity());
  }
  if (str == "-inf") {
    return Literal(-std::numeric_limits<double>::infinity());
  }
  return Literal();
}

static Literal parse(const std::string& str) {
  if (str.empty()) {
    return Literal();
  }

  const Literal pseudo = parsePseudoLiteral(str);
  if (pseudo.getType() != Literal::kInvalid) {
    return pseudo;
  }

  if (str.length() == 1 && !std::isdigit(static_cast<unsigned char>(str[0]))) {
    return Literal(str[0]);
  }

  const bool is_integer = isIntegerForm(str);
  const bool is_float = str[str.length() - 1] == 'f' &&
                        isDecimalForm(str.substr(0, str.length() - 1));
  const bool is_double = isDecimalForm(str);
  if (!is_integer && !is_float && !is_double) {
    return Literal();
  }

  const double value = std::strtod(str.c_str(), NULL);
  const double infinity = std::numeric_limits<double>::infinity();
  if (value == infinity || value == -infinity) {
    return Literal();
  }
  if (is_integer && fitsInInt(value)) {
    return Literal(static_cast<int>(value));
  }
  if (is_float && fitsInFloat(value)) {
    return Literal(static_cast<float>(value));
  }
  return Literal(value);
}

static ScalarValues cast(const Literal& literal) {
  ScalarValues values;

  switch (literal.getType()) {
    case Literal::kChar: {
      char c = literal.getChar();
      values.setChar(c);
      values.setInt(static_cast<int>(c));
      values.setFloat(static_cast<float>(c));
      values.setDouble(static_cast<double>(c));
      break;
    }
    case Literal::kInt: {
      int i = literal.getInt();
      if (fitsInChar(i)) {
        values.setChar(static_cast<char>(i));
      }
      values.setInt(i);
      values.setFloat(static_cast<float>(i));
      values.setDouble(static_cast<double>(i));
      break;
    }
    case Literal::kFloat: {
      float f = literal.getFloat();
      if (fitsInChar(f)) {
        values.setChar(static_cast<char>(f));
      }
      if (fitsInInt(f)) {
        values.setInt(static_cast<int>(f));
      }
      values.setFloat(f);
      values.setDouble(static_cast<double>(f));
      break;
    }
    case Literal::kDouble: {
      double d = literal.getDouble();
      if (fitsInChar(d)) {
        values.setChar(static_cast<char>(d));
      }
      if (fitsInInt(d)) {
        values.setInt(static_cast<int>(d));
      }
      if (fitsInFloat(d)) {
        values.setFloat(static_cast<float>(d));
      }
      values.setDouble(d);
      break;
    }
    case Literal::kInvalid:
      break;
  }

  return values;
}

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
  std::cout << format(cast(parse(literal)));
}

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter&) {}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter&) {
  return *this;
}

ScalarConverter::~ScalarConverter() {}
