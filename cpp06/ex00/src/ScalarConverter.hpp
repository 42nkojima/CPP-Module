#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>

class ScalarConverter {
 public:
  static void convert(const std::string& literal);

 private:
  ScalarConverter();
  ScalarConverter(const ScalarConverter& copy);

  ScalarConverter& operator=(const ScalarConverter& copy);

  ~ScalarConverter();
};

#endif
