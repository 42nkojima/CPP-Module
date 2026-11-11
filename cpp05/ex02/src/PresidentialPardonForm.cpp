#include "PresidentialPardonForm.hpp"

#include <iostream>

#include "AForm.hpp"

PresidentialPardonForm::PresidentialPardonForm()
    : AForm("nkoji", kGardenToSign, kGardenToExecute), target("default") {}

PresidentialPardonForm::PresidentialPardonForm(const std::string& target)
    : AForm("nkoji", kGardenToSign, kGardenToExecute), target(target) {}

PresidentialPardonForm::PresidentialPardonForm(
    const PresidentialPardonForm& copy)
    : AForm(copy), target(copy.target) {}

PresidentialPardonForm::~PresidentialPardonForm() {}

PresidentialPardonForm& PresidentialPardonForm::operator=(
    const PresidentialPardonForm& copy) {
  if (this != &copy) {
    AForm::operator=(copy);
  }
  return *this;
}

void PresidentialPardonForm::executeAction() const {
  std::cout << target << " has been pardoned by Zaphod Beeblebrox.\n";
}
