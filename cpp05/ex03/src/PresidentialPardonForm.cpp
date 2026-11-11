#include "PresidentialPardonForm.hpp"

#include <iostream>

#include "AForm.hpp"

PresidentialPardonForm::PresidentialPardonForm()
    : AForm("presidential pardon", kGradeToSign, kGradeToExecute),
      target_("default") {}

PresidentialPardonForm::PresidentialPardonForm(const std::string& target)
    : AForm("presidential pardon", kGradeToSign, kGradeToExecute),
      target_(target) {}

PresidentialPardonForm::PresidentialPardonForm(
    const PresidentialPardonForm& copy)
    : AForm(copy), target_(copy.target_) {}

PresidentialPardonForm& PresidentialPardonForm::operator=(
    const PresidentialPardonForm& copy) {
  if (this != &copy) {
    AForm::operator=(copy);
  }
  return *this;
}

PresidentialPardonForm::~PresidentialPardonForm() {}

void PresidentialPardonForm::executeAction() const {
  std::cout << target_ << " has been pardoned by Zaphod Beeblebrox.\n";
}
