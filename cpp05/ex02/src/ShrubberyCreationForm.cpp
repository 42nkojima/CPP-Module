#include "ShrubberyCreationForm.hpp"

#include <fstream>
#include <iostream>

#include "AForm.hpp"

const char* ShrubberyCreationForm::FileOpenException::what() const throw() {
  return "ShrubberyCreationForm: cannot open the output file";
}

ShrubberyCreationForm::ShrubberyCreationForm()
    : AForm("shrubbery creation", kGardenToSign, kGardenToExecute),
      target_("default") {}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
    : AForm("shrubbery creation", kGardenToSign, kGardenToExecute),
      target_(target) {}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& copy)
    : AForm(copy), target_(copy.target_) {}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(
    const ShrubberyCreationForm& copy) {
  if (this != &copy) {
    AForm::operator=(copy);
  }
  return *this;
}

void ShrubberyCreationForm::executeAction() const {
  const std::string filename = target_ + "_shrubbery";
  std::ofstream file(filename.c_str());
  if (!file) {
    throw FileOpenException();
  }
  file << "  ^     ^\n"
          " ^^^   ^^^\n"
          "  |     |\n";
}
