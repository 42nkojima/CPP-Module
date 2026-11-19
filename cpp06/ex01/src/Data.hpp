#ifndef DATA_HPP
#define DATA_HPP

#include <string>

struct Data {
  Data();
  Data(const Data& copy);

  Data& operator=(const Data& copy);

  ~Data();

  std::string name;
  int value;
};

#endif
