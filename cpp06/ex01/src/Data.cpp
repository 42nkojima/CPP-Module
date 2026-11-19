#include "Data.hpp"

Data::Data() : name(""), value(0) {}

Data::Data(const Data& copy) : name(copy.name), value(copy.value) {}

Data& Data::operator=(const Data& copy) {
  if (this != &copy) {
    name = copy.name;
    value = copy.value;
  }
  return *this;
}

Data::~Data() {}
