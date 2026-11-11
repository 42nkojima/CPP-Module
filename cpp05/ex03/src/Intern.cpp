#include "Intern.hpp"

#include <iostream>

Intern::Intern() {}

Intern::Intern(const Intern&) {}

Intern::~Intern() {}

Intern& Intern::operator=(const Intern&) { return *this; }

const char* Intern::UnknownFormException::what() const throw() {
  return "Intern: that form is unknown";
}

AForm* Intern::makeForm(const std::string& form_name,
                        const std::string& target) const {
  try {
    newFormByName(form_name, target);
    std::cout << "Intern creates " << form_name << "\n";
  } catch (std::exception& e) {
    std::cout << e.what() << ".\n";
  }
}

static AForm* newFormByName(const std::string& form_name,
                            const std::string& target) {
  std::string names[3] = {"shrubbery creation", "robotomy request",
                          "presidential pardon"};
  AForm* (*f[])(const std::string& target) = {};

  for (int i = 0; i < 3; ++i) {
    if (names[i] != target) {
      throw Intern::UnknownFormException();
    }
  }

  return *f;
}
