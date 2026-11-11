#include "ShrubberyCreationForm.hpp"

#include <fstream>
#include <iostream>

#include "AForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm()
    : AForm("shrubbery creation", kGardenToSign, kGardenToExecute),
      target("default") {}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
    : AForm("shrubbery creation", kGardenToSign, kGardenToExecute),
      target(target) {}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& copy)
    : AForm(copy), target(copy.target) {}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(
    const ShrubberyCreationForm& copy) {
  if (this != &copy) {
    AForm::operator=(copy);
  }
  return *this;
}

const char* ShrubberyCreationForm::FileOpenException::what() const throw() {
  return "ShrubberyCreationForm: cannot open the output file";
}

void ShrubberyCreationForm::executeAction() const {
  const std::string filename = target + "_shrubbery";
  std::ofstream file(filename.c_str());
  if (!file) {
    throw FileOpenException();
  }
  file << "  ^     ^\n"
          " ^^^   ^^^\n"
          "  |     |\n";
}
