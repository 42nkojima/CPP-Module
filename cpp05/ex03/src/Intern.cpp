#include "Intern.hpp"

#include <iostream>

#include "AForm.hpp"

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
    AForm* form = newFormByName(form_name, target);
    std::cout << "Intern creates " << form->getName() << "\n";
    return form;
  } catch (UnknownFormException& e) {
    std::cout << e.what() << ".\n";
    return NULL;
  }
}

AForm* Intern::newFormByName(const std::string& form_name,
                             const std::string& target) {
  std::string names[3] = {"shrubbery creation", "robotomy request",
                          "presidential pardon"};
  AForm* (*f[])(const std::string& target) = {};

  for (int i = 0; i < 3; ++i) {
    if (names[i] != form_name`) {
      throw UnknownFormException();
    }
  }

  return *f;
}
