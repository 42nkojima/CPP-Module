#include "Intern.hpp"

#include <iostream>

#include "AForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

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
    std::cout << "Intern couldn't create " << form_name << " because "
              << e.what() << ".\n";
    return NULL;
  }
}

static AForm* newShrubberyCreationForm(const std::string& target) {
  return new ShrubberyCreationForm(target);
}

static AForm* newRobotomyRequestForm(const std::string& target) {
  return new RobotomyRequestForm(target);
}

static AForm* newPresidentialPardonForm(const std::string& target) {
  return new PresidentialPardonForm(target);
}

AForm* Intern::newFormByName(const std::string& form_name,
                             const std::string& target) {
  std::string names[kNumForms] = {"shrubbery creation", "robotomy request",
                                  "presidential pardon"};
  AForm* (*f[kNumForms])(const std::string& target) = {
      newShrubberyCreationForm, newRobotomyRequestForm,
      newPresidentialPardonForm};

  for (int i = 0; i < kNumForms; ++i) {
    if (names[i] == form_name) {
      return f[i](target);
    }
  }
  throw UnknownFormException();
}
